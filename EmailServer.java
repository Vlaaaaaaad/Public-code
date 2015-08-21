import java.io.*;
import java.net.*;
import java.util.*;

class Mailbox
{
	public String username;
	protected Stack<String> emails;
	private int email_count;

	private static final int MAX_EMAILS = 10;

	Mailbox(String user)
	{
		username = user;

		email_count = 0;

		emails = new Stack<String>();
	}

	int size()
	{
		return email_count;
	}

	void put_email(String email)
	{
		if(email_count < MAX_EMAILS)
		{
			emails.add(email);
			email_count++;
		}
	}

	String get_email()
	{
		email_count--;

		if(email_count >= 0)
			return emails.pop();
		else
			return "User has no messages.";
	}
}

//--------------------------------------------------------------------------------------------------------------------//

public class EmailServer
{
	private static ServerSocket serverSocket;
	private static final int PORT = 1234;

	private static ArrayList<Mailbox> mailbox;
	private static int exit = 0;

	public static void main(String[] args)
	{
		System.out.println("Opening port...\n");

		try
		{
			serverSocket = new ServerSocket(PORT);
		}
		catch(IOException ioEx)
		{
			System.out.println("Unable to attach to port!");
			System.exit(1);
		}

		mailbox = new ArrayList<Mailbox>();

		// mailbox.add(new Mailbox("Dave"));
		// mailbox.add(new Mailbox("Karen"));

		do
		{
			handleClient();
		}while(exit != 1);

		exit = 0;

		do
		{
			handleClient();
		}while(exit != 1);

		System.out.println("Closing server...");

		System.exit(0);
	}

	private static void handleClient()
	{
		Socket link = null;

		try
		{
			link = serverSocket.accept();

			Scanner input = new Scanner(link.getInputStream());
			PrintWriter output = new PrintWriter(link.getOutputStream(), true);

			int numMessages = 0;
			String message = input.nextLine();

			String message_parts[] = new String[3]; // messages have at most 3 parts: USER_NAME COMMAND TEXT

			message_parts = message.split(" ", 3);

			while (!message_parts[1].equalsIgnoreCase("quit"))
			{
				message_parts = message.split(" ", 3);

				int found = 0;
				for(int i = 0; i < mailbox.size(); i++)
					if(mailbox.get(i).username.equalsIgnoreCase(message_parts[0]))
						found = 1;

				if(found == 0)
				{
					output.println("1");
					output.println("INVALID USER.");
					continue;
				}

				if(message_parts[1].equalsIgnoreCase("read"))
				{
					for(int i = 0; i < mailbox.size(); i++)
						if(mailbox.get(i).username.equalsIgnoreCase(message_parts[0]))
						{
							output.println(String.valueOf(mailbox.get(i).size() + 1));
							output.println("Number of messages in inbox "
										+ mailbox.get(i).size());

							while(mailbox.get(i).size() != 0)
							{
								output.println(mailbox.get(i).get_email());
							}
						}
				}
				else if(message_parts[1].equalsIgnoreCase("send"))
				{
					for(int i = 0; i < mailbox.size(); i++)
						if(mailbox.get(i).username.equalsIgnoreCase(message_parts[0]))
							mailbox.get(i).put_email(message_parts[2]);

					output.println("1");
					output.println("Message sent.");
				}
				else
				{
					output.println("1");
					output.println("INVALID COMMAND.");
				}

				System.out.println("Message received: " + message);

				message = input.nextLine();
			}
		}

		catch(IOException ioEx)
		{
			ioEx.printStackTrace();
		}
		finally
		{
			try
			{
				System.out.println("\n* Closing connection to client... *");
				exit = 1;
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
