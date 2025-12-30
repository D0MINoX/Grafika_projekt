using GK2025CLI;
using Microsoft.Win32;
using Microsoft.Win32.SafeHandles;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
namespace GK2025_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        GKWrapper gk = new GKWrapper();

        public MainWindow()
        {
            InitializeComponent();
            ZaladujListeObrazow();

        }
        private void ZaladujListeObrazow()
        {
            image_selection.Items.Clear();
            string folder = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Images");

            if (!Directory.Exists(folder))
                return;

            var pliki = Directory.GetFiles(folder, "*.bmp");

            foreach (var plik in pliki)
            {
                image_selection.Items.Add(System.IO.Path.GetFileName(plik));
            }
        }
        private void ZapiszBitmap(BitmapImage bmp, string sciezka)
        {
            BmpBitmapEncoder encoder = new BmpBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bmp));

            using (FileStream fs = new FileStream(sciezka, FileMode.Create))
            {
                encoder.Save(fs);
            }
        }

        private BitmapImage SkalujObraz(BitmapImage input, int width, int height)
        {
            TransformedBitmap tb = new TransformedBitmap(
                input,
                new ScaleTransform(
                    (double)width / input.PixelWidth,
                    (double)height / input.PixelHeight
                )
            );

            // Konwersja do BitmapImage
            JpegBitmapEncoder encoder = new JpegBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(tb));

            using (MemoryStream ms = new MemoryStream())
            {
                encoder.Save(ms);
                ms.Position = 0;

                BitmapImage result = new BitmapImage();
                result.BeginInit();
                result.StreamSource = ms;
                result.CacheOption = BitmapCacheOption.OnLoad;
                result.EndInit();
                return result;
            }
        }

        private void PrzetworzObraz(string sciezkaWejsciowa)
        {
            string folderDocelowy = System.IO.Path.Combine(
                AppDomain.CurrentDomain.BaseDirectory,
                "Images"
            );

            if (!Directory.Exists(folderDocelowy))
                Directory.CreateDirectory(folderDocelowy);

            string nazwaPliku = System.IO.Path.GetFileName(sciezkaWejsciowa);
            string sciezkaWyjsciowa = System.IO.Path.Combine(folderDocelowy, nazwaPliku);

            // Wczytaj obraz
            BitmapImage bmp = new BitmapImage(new Uri(sciezkaWejsciowa));

            // Jeśli ma złe wymiary → skaluj
            if (bmp.PixelWidth != 320 || bmp.PixelHeight != 200)
            {
                bmp = SkalujObraz(bmp, 320, 200);
            }

            // Zapisz jako BMP
            ZapiszBitmap(bmp, sciezkaWyjsciowa);
            ZaladujListeObrazow();
            MessageBox.Show("Obraz zapisany: " + sciezkaWyjsciowa);
        }
        private void StartSDL_Click(object sender, RoutedEventArgs e)
        {
            gk.StartSDL();
        }

        private void ladujBMP_Click(object sender, RoutedEventArgs e)
        {
            if (image_selection.SelectedItem == null)
            {
                MessageBox.Show("Please select an image from the list.");
                return;
            }
            string nazwaPliku = image_selection.Text;

            string sciezka = System.IO.Path.Combine(
                AppDomain.CurrentDomain.BaseDirectory,
                "Images",
                nazwaPliku
            );

            gk.LoadBMP(sciezka, 0, 0);
        }
        private async void paleta_Click(object sender, RoutedEventArgs e)
        {
            loading_block.Visibility = Visibility.Visible;
            int select = paleta_selection.SelectedIndex;
            await Task.Run(() =>
            {
                switch (select)
                {
                    case 0:
                        gk.palette_imposeed();
                        break;
                    case 1:
                        gk.palette_imposeed_gray();
                        break;
                    case 2:
                        gk.palette_median_cut();
                        break;
                    case 3:
                        gk.palette_median_cut_gray();
                        break;
                    case 4:
                        gk.palette_imposeed_bit();
                        break;
                    default:
                        MessageBox.Show("Please select a palette from the list.");
                        return;

                }
            });

            loading_block.Visibility = Visibility.Collapsed;



        }
        private void dithering_Click(object sender, RoutedEventArgs e)
        {
            int select = dithering_selection.SelectedIndex;
            switch (select)
            {
                case 0:
                    gk.bayer_dithering_gray();
                    break;
                case 1:
                    gk.bayer_dithering();
                    break;

                default:
                    MessageBox.Show("Please select a dithering from the list.");
                    return;

            }
        }


        private void AddFile_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Bitmapy (*.bmp)|*.bmp";
            dialog.Title = "Wybierz obraz BMP";

            if (dialog.ShowDialog() == true)
            {
                PrzetworzObraz(dialog.FileName);
            }

        }
        private void SafeFileBin_Click(object sender, RoutedEventArgs e)
        {

            if (image_selection.SelectedItem == null)
            {
                MessageBox.Show("Please select an image from the list.");
                return;
            }
            else
            {
                char identyfikator = file_selection.SelectedIndex.ToString()[0];
                MessageBox.Show("/"+identyfikator+"/");
                if (identyfikator == '0')
                {
                    gk.save_file();
                    MessageBox.Show("Zapisano do pliku obrazRGB.bin");
                }
                else
                {
                    gk.save_file_5(identyfikator);
                    MessageBox.Show("Zapisano do pliku obraz5.bin");
                }
            }

        }
        private void LoadFileBin_Click(object sender, RoutedEventArgs e)
        {

            gk.load_file_5();
        }
    }
}