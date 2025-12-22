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
using GK2025CLI;
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
        }
        private void StartSDL_Click(object sender, RoutedEventArgs e)
        {
            gk.StartSDL();
        }

        private void ladujBMP_Click(object sender, RoutedEventArgs e)
        {
            int select = image_selection.SelectedIndex;
            switch (select)
            {
                case 0:
                    gk.LoadBMP("obrazek1.bmp", 0, 0);
                    break;
                case 1:
                    gk.LoadBMP("obrazek2.bmp", 0, 0);
                    break;
                case 2:
                    gk.LoadBMP("obrazek3.bmp", 0, 0);
                    break;
                case 3:
                    gk.LoadBMP("obrazek4.bmp", 0, 0);
                    break;
                case 4:
                    gk.LoadBMP("obrazek5.bmp", 0, 0);
                    break;
                case 5:
                    gk.LoadBMP("obrazek6.bmp", 0, 0);
                    break;
                case 6:
                    gk.LoadBMP("obrazek7.bmp", 0, 0);
                    break;
                case 7:
                    gk.LoadBMP("obrazek8.bmp", 0, 0);
                    break;
                case 8:
                    gk.LoadBMP("obrazek9.bmp", 0, 0);
                    break;
                default:
                    MessageBox.Show("Please select an image from the list.");
                    return;
            }
        }
        private void paleta_Click(object sender, RoutedEventArgs e)
        {
            int select = paleta_selection.SelectedIndex;
            switch (select)
            {
                case 0:
                    gk.palette_imposeed();
                    break;
                case 1:
                    gk.palette_imposeed_gray();
                    break;
                default :
                    MessageBox.Show("Please select a palette from the list.");
                    return;

            }
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
        }
}