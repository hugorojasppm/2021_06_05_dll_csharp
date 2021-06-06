using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Consumerv2
{
    class Program
    {

        public const string DllPath = "e:\\projects\\fixed\\linux-windows-csharp\\Hello\\x64\\Debug\\Crypt.dll";


        [DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        private static extern string CryptData([MarshalAs(UnmanagedType.LPStr)] string data);

        [DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        private static extern string DecryptData([MarshalAs(UnmanagedType.LPStr)] string encoded_data, int data_size);

        static void Main(string[] args)
        {
            string dataToEncrypt =  "[{\"name\":\"Leanne Graham\",\"email\":\"Sincere @april.biz\",\"phone\":\"1 - 770 - 736 - 8031 x56442\",\"website\":\"hildegard.org\"},{\"name\":\"Ervin Howell\",\"email\":\"Shanna @melissa.tv\",\"phone\":\"010 - 692 - 6593 x09125\",\"website\":\"anastasia.net\"},{\"name\":\"Clementine Bauch\",\"email\":\"Nathan @yesenia.net\",\"phone\":\"1 - 463 - 123 - 4447\",\"website\":\"ramiro.info\"},{\"name\":\"Patricia Lebsack\",\"email\":\"Julianne.OConner @kory.org\",\"phone\":\"493 - 170 - 9623 x156\",\"website\":\"kale.biz\"},{\"name\":\"Chelsey Dietrich\",\"email\":\"Lucio_Hettinger @annie.ca\",\"phone\":\"(254)954 - 1289\",\"website\":\"demarco.info\"},{\"name\":\"Mrs.Dennis Schulist\",\"email\":\"Karley_Dach @jasper.info\",\"phone\":\"1 - 477 - 935 - 8478 x6430\",\"website\":\"ola.org\"},{\"name\":\"Kurtis Weissnat\",\"email\":\"Telly.Hoeger @billy.biz\",\"phone\":\"210.067.6132\",\"website\":\"elvis.io\"},{\"name\":\"Nicholas Runolfsdottir V\",\"email\":\"Sherwood @rosamond.me\",\"phone\":\"586.493.6943 x140\",\"website\":\"jacynthe.com\"},{\"name\":\"Glenna Reichert\",\"email\":\"Chaim_McDermott @dana.io\",\"phone\":\"(775)976 - 6794 x41206\",\"website\":\"conrad.com\"},{\"name\":\"Clementina DuBuque\",\"email\":\"Rey.Padberg @karina.biz\",\"phone\":\"024 - 648 - 3804\",\"website\":\"ambrose.net\"}]";

            int data_size = dataToEncrypt.Length;
            Console.WriteLine("start encrypt");
            string resultCrypt = CryptData(dataToEncrypt);

            Console.WriteLine(resultCrypt);

            Console.WriteLine("start decrypt");
            string resultDecrypt = DecryptData(resultCrypt, data_size);

            Console.WriteLine(resultDecrypt);

        }
    }
}
