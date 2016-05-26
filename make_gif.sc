package GIFReader

// including libraries
import java.awt.image.BufferedImage
import scodec.codecs._
import scala.NoSuchElementException
import java.awt.{Color, Graphics2D, Dimension}
import bits._
import java.util.{MissingResourceException, IllegalFormatException}
import swing.{Panel, MainFrame, SimpleSwingApplication}
import java.io._
import scodec._
import java.nio.file.{Files, Paths}
import scodec.bits.ByteOrdering.LittleEndian

// main class
class ImagePanel(data: Array[Array[Color]]) extends Panel {
  override def paintComponent(g: Graphics2D) {
    val width = data.length
    val height = data.map(_.length).max
    val dx = g.getClipBounds.width.toFloat  / width
    val dy = g.getClipBounds.height.toFloat / height
    for {
      x <- 0 until data.length
      y <- 0 until data(x).length
      x1 = (x * dx).toInt
      y1 = (y * dy).toInt
      x2 = ((x + 1) * dx).toInt
      y2 = ((y + 1) * dy).toInt
    } {
      data(x)(y) match {
        case c: Color => g.setColor(c)
        case _ => g.setColor(Color.WHITE)
      }
      g.fillRect(x1, y1, x2 - x1, y2 - y1)
    }
  }
}

// Timer
object SetTimeout {
  def apply(interval: Int, repeats: Boolean = true)(op: => Unit) {
    val timeOut = new javax.swing.AbstractAction() {
      def actionPerformed(e : java.awt.event.ActionEvent) = op
    }
    val t = new javax.swing.SetTimeout(interval, timeOut)
    t.setRepeats(repeats)
    t.start()
  }
}

object TDraw extends SimpleSwingApplication {
  case class gif_header (width: Int, height: Int, GCT_flag: Boolean, color_resolution: Int, SF_flag: Boolean,
                         GCT_size: Int, background_color: Int, ratio: Int)
  case class image (LP: Int, TP: Int, width: Int, height: Int, LCT_flag: Boolean, interlace_flag: Boolean,
                    sort_flag: Boolean, reserved_bits: Int, LCT_size: Int)
  case class animation (disposal_method: Int, UI_flag: Boolean, TC_flag: Boolean, delay: Int, transparent_color: Int)
  case class gif_file (header: gif_header, global_color_table: Array[Int], image_descriptors: List[image],
                       images: List[Array[Int]], animations: List[animation])
  def LZW(min_root: Int, input: BitVector, CT: List[Int]): Array[Int] = {
    def listofarrays(list: List[Int], acc: List[Array[Int]]): List[Array[Int]] = {
      if (list.isEmpty) {
        acc.reverse
      }
      else {
        listofarrays(list.tail, Array(list.head) :: acc)
      }
    }
    def iter(size_of_elem: Int, prefix: Array[Int], in: BitVector, table: List[Array[Int]], out: Array[Int],
             end_elem: Int): Array[Int] = {
      val elem = in.take(size_of_elem).reverseBitOrder.toInt(false, LittleEndian)
      if (elem == end_elem) {
        out
      }
      else if (elem < table.length) {
        val new_table = table ::: List((prefix :+ table(elem)(0)))
        val new_out = out ++ table(elem)
        iter(1 + (Math.log(new_table.length) / Math.log(2)).toInt, table(elem), in.drop(size_of_elem),
          new_table, new_out, end_elem)
      }
      else {
        val new_table = table ::: List((prefix :+ prefix(0)))
        val new_out = out ++ (prefix :+ prefix(0))
        iter(1 + (Math.log(new_table.length) / Math.log(2)).toInt, prefix :+ prefix(0), in.drop(size_of_elem),
          new_table, new_out, end_elem)
      }
    }
    val clear_elem = input.take(min_root).reverseBitOrder.toInt(false, LittleEndian)
    val first_elem = input.drop(min_root).take(min_root).reverseBitOrder.toInt(false, LittleEndian)
    iter(min_root, Array(CT(first_elem)), input.drop(2 * min_root), listofarrays(CT, Nil),
      Array(CT(first_elem)), clear_elem + 1)
  }
  def decoder(path: String): gif_file = {
    val headerCodec = (uint16L :: uint16L :: bool :: uintL(3) :: bool :: uintL(3) :: uint8L :: uint8L).as[gif_header]
    val imageCodec = (uint16L :: uint16L :: uint16L :: uint16L :: bool :: bool :: bool :: uint2L :: uintL(3)).as[image]
    val animationCodec = (uintL(3) :: bool :: bool :: uint16L :: uint8L).as[animation]
    def create_color_table(table: Array[Int], size: Int, vector: BitVector): Array[Int] = {
      if (size == 0) {
        table
      }
      else {
        val red = vector.take(8).toInt(false, LittleEndian)
        val green = vector.drop(8).take(8).toInt(false, LittleEndian)
        val blue = vector.drop(16).take(8).toInt(false, LittleEndian)
        val new_color = red * 1000000 + green * 1000 + blue 
        create_color_table(table :+ new_color, size - 1, vector.drop(24))
      }
    }
    def dropper(vector: BitVector): BitVector = {
      val size = vector.take(8).toInt(false, LittleEndian)
      val new_vector = vector.drop(8)
      if (size == 0) {
        new_vector
      }
      else {
        dropper(new_vector.drop(8 * size))
      }
    }
    def get_image(vec: BitVector, acc: BitVector): BitVector = {
      def reversebits(in_bl: BitVector, ou_bl: BitVector): BitVector = {
        if (in_bl.isEmpty) {
          ou_bl
        }
        else {
          reversebits(in_bl.drop(8), ou_bl ++ in_bl.take(8).reverseBitOrder)
        }
      }
      val size = vec.take(8).toInt(false, LittleEndian)
      var vector = vec.drop(8)
      if (size == 0) {
        acc
      }
      else {
        val block = vector.take(size * 8)
        get_image(vector.drop(size * 8), acc ++ reversebits(block, BitVector(Nil)))
      }
    }
    def descriptor_cases(vector: BitVector, giffile: gif_file): gif_file = {
      val extension = vector.take(8).toInt(false, LittleEndian)
      if (extension == 44) {
        val new_image_descriptor = imageCodec.decode(vector.drop(8)).require.value
        var new_LCT: Array[Int] = Array[Int]()
        var new_vector = vector.drop(8).drop(9 * 8)
        if (new_image_descriptor.LCT_flag) {
          new_LCT = create_color_table(new_LCT, Math.pow(2, new_image_descriptor.LCT_size + 1).toInt, vector)
          new_vector = new_vector.drop(Math.pow(2, new_image_descriptor.LCT_size + 1).toInt * 3 * 8)
        }
        val root = (new_vector.take(8).toInt(false, LittleEndian))
        new_vector = new_vector.drop(8)
        var image_vector = get_image(new_vector, BitVector(Nil))
        var CT: Array[Int] = Array[Int]()
        if (new_image_descriptor.LCT_flag) {
          CT = new_LCT
        }
        else {
          CT = giffile.global_color_table
        }
        val new_image = LZW(root + 1, image_vector, CT.toList ::: List(1000000000, 2000000000))
        val new_gif = new gif_file(giffile.header, giffile.global_color_table, new_image_descriptor ::
          giffile.image_descriptors, new_image :: giffile.images,
          giffile.animations)
        new_vector = dropper(new_vector)
        descriptor_cases(new_vector, new_gif)
      }
      else if (extension == 59) {
        val gif_out = new gif_file(giffile.header, giffile.global_color_table, giffile.image_descriptors.reverse,
          giffile.images.reverse, giffile.animations.reverse)
        gif_out
      }
      else if (extension == 33) {
        val label = vector.drop(8).take(8).toInt(false, LittleEndian)
        if (label == 249) {
          val new_animation = animationCodec.decode(vector.drop(27)).require.value
          val new_gif = new gif_file(giffile.header, giffile.global_color_table, giffile.image_descriptors,
            giffile.images, new_animation :: giffile.animations)
          descriptor_cases(vector.drop(16).drop(6 * 8), new_gif)
        }
        else if (label == 254) {
          val new_vector = dropper(vector.drop(16))
          descriptor_cases(new_vector, giffile)
        }
        else if (label == 1) {
          val new_vector = dropper(vector.drop(16).drop(13 * 8))
          descriptor_cases(new_vector, giffile)
        }
        else if (label == 255) {
          val new_vector = dropper(vector.drop(16))
          descriptor_cases(new_vector, giffile)
        }
        else {
          throw new NoSuchElementException()
        }
      }
      else {
        throw new NoSuchElementException()
      }
    }
    val byteArray = Files.readAllBytes(Paths.get(path))
    var bitVector = (BitVector(byteArray)).drop(48)
    val decoded_header = headerCodec.decode(bitVector).require.value
    bitVector = bitVector.drop(7 * 8)
    var GCT: Array[Int] = Array[Int](0)
    if (decoded_header.GCT_flag) {
      GCT = create_color_table(Array[Int](), Math.pow(2, decoded_header.GCT_size + 1).toInt, bitVector)
      bitVector = bitVector.drop(Math.pow(2, decoded_header.GCT_size + 1).toInt * 3 * 8)
    }
    val file = new gif_file(decoded_header, GCT, Nil, Nil, Nil)
    descriptor_cases(bitVector, file)
  }
  def color(col: Int): Color = {
    new Color(col / 1000000, (col / 1000) % 1000, col % 1000)
  }
  def get_frames(ims: List[Array[Int]], dscs: List[image], acc: List[Array[Array[Color]]]): List[Array[Array[Color]]] = {
    def frame(back: Array[Array[Color]], im: Array[Int], w: Int, h: Int, desc: image): Array[Array[Color]] = {
      val new_frame = back
      var i = 0
      for {
        x <- 0 until w
        y <- 0 until h
      } {
        if (x >= desc.LP && y>= desc.TP) {
          new_frame(x)(y) = color(im(i))
          i = i + 1
        }
      }
      new_frame
    }
    if(ims.isEmpty) {
      acc
    }
    else {
      get_frames(ims.tail, dscs.tail, acc :+ frame(Array.fill(gif.header.width,
        gif.header.height)(color(gif.global_color_table(gif.header.background_color))), ims.head,
        gif.header.width, gif.header.height, dscs.head))
    }
  }
  val file_name = "imagex.gif";
  val gif: gif_file = decoder(file_name)
  val scale = 30
  val back = Array.fill(gif.header.width, gif.header.height)(color(gif.global_color_table(gif.header.background_color)))
  val frames = get_frames(gif.images, gif.image_descriptors, Nil).toArray
  val module = frames.length
  var number = 0
  def top = new MainFrame {
    def tick() = {
      var disp_method = gif.animations(number % module).disposal_method
      if (disp_method == 3) {
        contents = new ImagePanel(frames((number - 1) % module)) {
          preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
        }
      }
      else if (disp_method == 2) {
        contents = new ImagePanel(back) {
          preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
        }
      }
      number += 1
      contents = new ImagePanel(frames((number - 1) % module)) {
        preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
      }
    }
    SetTimeout(gif.animations(number % module).delay) {tick()}
  }
}