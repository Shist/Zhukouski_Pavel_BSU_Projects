using System.Linq;

namespace Lab1
{
    public class Crypt
    {
        const string defaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        readonly string letters;

        public Crypt(string alphabet = null)
        {
            letters = string.IsNullOrEmpty(alphabet) ? defaultAlphabet : alphabet;
        }


        private string Vigenere(string text, string password, bool encrypting = true)
        {
            return new string(text.Select((symbol, index) =>letters.Contains(symbol)? letters[
                    (
                        letters.Length
                        + letters.IndexOf(symbol)
                        + (encrypting ? 1:-1)*letters.IndexOf(password[index % password.Length]
                        )
                    ) % letters.Length]: symbol
                )
               .ToArray());
        }


        public string Encrypt(string plainMessage, string password)
            => Vigenere(plainMessage, password);


        public string Decrypt(string encryptedMessage, string password)
            => Vigenere(encryptedMessage, password, false);
    }
}