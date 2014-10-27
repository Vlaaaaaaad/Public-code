import java.util.*;
import java.io.*;

public class DiceThrows
{
	public static void main(String[] args) throws Exception
	{
		int sides, throwss;

		Zar dice;

		Scanner sc = new Scanner(System.in);

		System.out.println("How many throws?");

		throwss = sc.nextInt();

		dice = new Zar();

		dice.throow(throwss);

		System.out.print(dice.toString());

		sc.close();
	}

}

class Zar
{
	int freq[];
	int sides;

	public Zar()
	{
		System.out.println("How many sides should the dice have?");

		Scanner sc = new Scanner(System.in);

		sides = sc.nextInt();

		freq = new int[sides * 2 + 1];

		sc.close();
	}

	void throow(int throwss)
	{
		Random R = new Random();

		for(int i = 0; i <= throwss; i++)
			freq[R.nextInt(sides) + R.nextInt(sides) + 2]++;
	}

	@Override
	public String toString()
	{
		String s;

		s = new String();

		for(int i1: freq)
			s += i1 + " ";

		return s;
	}

}
