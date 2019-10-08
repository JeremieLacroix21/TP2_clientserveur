using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace client
{
    class client
    {
        public static int Main(String[] args)
        {
            byte[] bytes = new byte[1024]; // Déclaration du buffer 
            try
            {
                string serverIP = "127.0.0.1"; int port = 8080;
                IPEndPoint remoteEP = new IPEndPoint(System.Net.IPAddress.Parse(serverIP), port);
                // Création de la ocket TCP/IP
                Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // Connecter la socket.
                try
                {
                    sender.Connect(remoteEP);
                    Console.WriteLine("Socket connectée à {0}", sender.RemoteEndPoint.ToString());
                    Console.Write("Votre texte: ");
                    string message = Console.ReadLine();
                    // Encoder le string en tableau de byte(octet)
                    byte[] msg = Encoding.ASCII.GetBytes(message);
                    // Envoyer le message au client.
                    int bytesSent = sender.Send(msg);
                    // Recevoir la réponse du serveur.
                    int bytesRec = sender.Receive(bytes);
                    Console.WriteLine("Texte reçu: {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
                    // Fermer la socket.
                    sender.Shutdown(SocketShutdown.Both); sender.Close();
                }
                catch (ArgumentNullException ane) { Console.WriteLine("ArgumentNullException : {0}", ane.ToString()); }
                catch (SocketException se) { Console.WriteLine("SocketException : {0}", se.ToString()); }
                catch (Exception e) { Console.WriteLine("Unexpected exception : {0}", e.ToString()); }
            }
            catch (Exception e) { Console.WriteLine(e.ToString()); }
            return 0;
        }
    }

}

