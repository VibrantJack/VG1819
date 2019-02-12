using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.IO;


namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            newimage:
            //open console
            InitializeComponent();

            //get path to texture - NOTE THAT TEXTURE SHOULD BE IN THE DEBUG FOLDER
            Console.Write("Enter .png file name - make sure your png is in the debug folder: \n");
            string pngPath = Console.ReadLine();
            Console.WriteLine("\nThanks. I'm pre-multiplying your texture now...");

            //set up image as a preview
            Image img = new Image();
            BitmapImage bi = new BitmapImage();
            bi.BeginInit();
            bi.UriSource = new Uri(pngPath, UriKind.RelativeOrAbsolute);
            bi.EndInit();

            //pixel data
            img.Width = bi.Width;
            img.Height = bi.Height;
            img.Source = bi;

            //show the picture
            Window w = new Window();
            w.Content = img;
            w.Show();

            //array navigation values
            int stride = bi.PixelWidth * 4;
            int size = bi.PixelHeight * stride;
            byte[] pixels = new byte[size];
            bi.CopyPixels(pixels, stride, 0);

            Console.WriteLine("\nBefore Bleeding...\n");

            //frequently used values as vars
            int index = 0;
            int indexStride = 4;
            int greenOff = 1;
            int blueOff = 2;
            int alpOff = 3;

            //for each pixel, check if it is next to a solid color pixel.
            foreach (byte px in pixels)
            {
                byte red = pixels[index];
                byte green = pixels[index + greenOff];
                byte blue = pixels[index + blueOff];
                byte alp = pixels[index + alpOff];

                Console.Write("Red: " + red + "; Green: " + blue + "; Blue: " + blue + "; Alpha: " + alp + "\n");

                //if this pixel is completely transparent
                if ((int)alp == 0)
                {
                    //temp values of adjacent pixels with color
                    byte tempRed, tempGreen, tempBlue, tempAlp;

                    //check if there is a pixel to the right that is not transparent
                    //if there is, bleed it's color into the current pixel
                    if (index + alpOff + indexStride <= pixels.Length)
                    {
                        tempAlp = pixels[index + alpOff + indexStride];
                        if ((float)tempAlp == 255)
                        {
                            //get the rgb of the right-adjacent non-transparent pixel
                            tempRed = pixels[index + indexStride];
                            tempGreen = pixels[index + greenOff + indexStride];
                            tempBlue = pixels[index + blueOff + indexStride];
                            
                            //bleed into next 5 pixels
                            for (int i = 0; i < 5; i++)
                            { 
                                if (pixels[index + alpOff - indexStride * i] < 255)
                                {
                                    pixels[index - indexStride * i] = tempRed;
                                    pixels[index + greenOff - indexStride * i] = tempGreen;
                                    pixels[index + blueOff - indexStride * i] = tempBlue;
                                    pixels[index + alpOff - indexStride * i] = (byte)0;
                                }
                            }
                        }
                    }

                    //check pixel to the left
                    if (index + alpOff - indexStride >= 0)
                    {
                        tempAlp = pixels[index + alpOff - indexStride];
                        if ((float)tempAlp == 255)
                        {
                            //get the rgb of the left-adjacent non-transparent pixel
                            tempRed = pixels[index - indexStride];
                            tempGreen = pixels[index + greenOff - indexStride];
                            tempBlue = pixels[index + blueOff - indexStride];

                            //bleed into right 5 pixels

                            for (int i = 0; i < 5; i++)
                            {
                                if (pixels[index + alpOff + indexStride * i] < 255)
                                {
                                    pixels[index + indexStride * i] = tempRed;
                                    pixels[index + greenOff + indexStride * i] = tempGreen;
                                    pixels[index + blueOff + indexStride * i] = tempBlue;
                                    pixels[index + alpOff + indexStride * i] = (byte)0;
                                }
                            }
                        }
                    }

                    //check pixel above this one
                    if (index + alpOff - (int)bi.PixelWidth * stride >= 0)
                    {
                        tempAlp = pixels[index + alpOff - (int)bi.PixelWidth * stride];
                        if ((float)tempAlp == 255)
                        {
                            //get the rgb of the left-adjacent non-transparent pixel
                            tempRed = pixels[index - (int)bi.PixelWidth];
                            tempGreen = pixels[index + greenOff - (int)bi.PixelWidth * stride];
                            tempBlue = pixels[index + blueOff - (int)bi.PixelWidth * stride];

                            //bleed into upper 5 pixels
                            
                            for (int i = 0; i < 5; i++)
                            {
                                if (pixels[index + alpOff + (int)bi.PixelWidth * stride * i] < 255)
                                {
                                    pixels[index + indexStride * i] = tempRed;
                                    pixels[index + greenOff + (int)bi.PixelWidth * stride * i] = tempGreen;
                                    pixels[index + blueOff + (int)bi.PixelWidth * stride * i] = tempBlue;
                                    pixels[index + alpOff + (int)bi.PixelWidth * stride * i] = (byte)0;
                                }
                            }
                        }
                    }

                    if (index + alpOff + (int)bi.PixelWidth * stride <= pixels.Length)
                    {
                        //check pixel below
                        tempAlp = pixels[index + alpOff + (int)bi.PixelWidth * stride];
                        if ((float)tempAlp == 255)
                        {
                            //get the rgb of the left-adjacent non-transparent pixel
                            tempRed = pixels[index + (int)bi.PixelWidth * stride];
                            tempGreen = pixels[index + greenOff + (int)bi.PixelWidth * stride];
                            tempBlue = pixels[index + blueOff + (int)bi.PixelWidth * stride];

                            //bleed into this pixel with half alpha
                            for (int i = 0; i < 5; i++)
                            {
                                if (pixels[index + alpOff - (int)bi.PixelWidth * stride * i] < 255)
                                {
                                    pixels[index - indexStride * i] = tempRed;
                                    pixels[index + greenOff - (int)bi.PixelWidth * stride * i] = tempGreen;
                                    pixels[index + blueOff - (int)bi.PixelWidth * stride * i] = tempBlue;
                                    pixels[index + alpOff - (int)bi.PixelWidth * stride * i] = (byte)0;
                                }
                            }
                        }
                    }
                }
                index += indexStride;
                if (index + 1 > pixels.Length)
                {
                    break;
                }
            }

            index = 0;

            //show new values for debugging...

            Console.WriteLine("\nAfter Bleeding...\n");

            foreach (byte px in pixels)
            {
                byte red = pixels[index];
                byte green = pixels[index + 1];
                byte blue = pixels[index + 2];
                byte alp = pixels[index + 3];

                Console.Write("Red: " + red + "; Green: " + blue + "; Blue: " + blue + "; Alpha: " + alp + "\n");

                index += 4;

                if (index + 1 > pixels.Length)
                {
                    break;
                }
            }

            //new bitmap with new pixels used to export and display

            BitmapSource bms = BitmapSource.Create(bi.PixelWidth, bi.PixelHeight, bi.DpiX, bi.DpiY, PixelFormats.Bgra32, BitmapPalettes.Halftone256, pixels, stride);
            Image newImg = new Image();
            newImg.Width = bi.Width;
            newImg.Height = bi.Height;
            newImg.Source = bms;

            //show new image
            w.Hide();
            w.Content = newImg;
            w.Show();

            //get filename and convert to png
            Console.WriteLine("Done. \n");
            Console.WriteLine("Enter a file name. Do not include the extension (.png). Do not use spaces.");
            string filename = Console.ReadLine();
            filename += ".png";

            FileStream stream = new FileStream(filename, FileMode.Create);
            PngBitmapEncoder encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bms));
            encoder.Save(stream);
            stream.Close();

            //check if there are more images to convert

            Console.WriteLine("All done. Do you want to clean another image? Press Y to continue. Press any other key to quit.");
            ConsoleKeyInfo key = Console.ReadKey();
            if(key.Key == ConsoleKey.Y)
            {
                //if yes, go back
                Console.WriteLine("\nOkay. Starting over.\n");
                goto newimage;
            } else
            {
                //if no, quit.
                Application.Current.Shutdown();
            }
        }
    }
}
