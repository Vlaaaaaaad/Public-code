import java.io.*;
import java.net.*;
import java.util.*;

public class EmailClient
{
	private static InetAddress host;
	private static final int PORT = 1234;

	public static void main(String[] args)
	{
		try
		{
			host = InetAddress.getLocalHost();
		}
		catch(UnknownHostException uhEx)
		{
			System.out.println("Host ID not found!");
			System.exit(1);
		}
		accessServer();
	}

	private static void accessServer()
	{
		Socket link = null;

		try
		{
			link = new Socket(host,PORT);
			Scanner input =	new Scanner(link.getInputStream());
			PrintWriter output = new PrintWriter(link.getOutputStream(), true);

			Scanner userEntry = new Scanner(System.in);

			String message, response, response_ct;
			String message_parts[] = new String[3];

			do
			{
				System.out.print("\nEnter command: ");
				message = userEntry.nextLine();
				output.println(message);

				response_ct = input.nextLine();
				for(Integer i = 0; i < Integer.parseInt(response_ct); i++)
				{
					response = input.nextLine();
					System.out.println("SERVER> " + response);
				}

				message_parts = message.split(" ", 3);
			}while (!message_parts[1].equalsIgnoreCase("quit"));

			output.println("Client is closing...");
		}
		catch(IOException ioEx)
		{
			ioEx.printStackTrace();
		}
		finally
		{
			try
			{
				System.out.println("\n* Closing connection... *");
				link.close();
			}
			catch(IOException ioEx)
			{
				System.out.println("Unable to disconnect!");
				System.exit(1);
			}
		}
	}
}
