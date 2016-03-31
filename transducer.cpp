#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <stdexcept>
#include <fstream>
#include <vector>

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

// empty transition
char epsilon = '?';

class road
{
private:
	// we're going on letter
	char m_letter;

	// and replacing the letter with
	std::string m_replace;

	// to the state with the id
	int m_goes_to_state_id;

public:
	road(char letter, std::string replace, int id)
	{
		m_letter = letter;
		m_replace = replace;
		m_goes_to_state_id = id;
	}

	/* ------------------------------------------------------------------ */

	char letter()
	{
		return m_letter;
	}

	/* ------------------------------------------------------------------ */

	std::string replace()
	{
		return m_replace;
	}

	/* ------------------------------------------------------------------ */

	int to()
	{
		return m_goes_to_state_id;
	}
};

/* -------------------------------------------------------------------------- */

class state
{
private:
	// state id
	int m_id;

	// if it's a final state or not
	bool m_final;

public:
	std::list<road> roads;

	/* ------------------------------------------------------------------ */

	state(int id)
	{
		m_id = id;
		m_final = false;
	}

	/* ------------------------------------------------------------------ */

	void add_road(char letter, std::string replace, int id)
	{
		// emplace_back
		//	- constructs the element
		//	- where we want it to be built
		roads.emplace_back(road(letter, replace, id));
	}

	/* ------------------------------------------------------------------ */

	int id()
	{
		return m_id;
	}

	/* ------------------------------------------------------------------ */

	bool is_final()
	{
		if(m_final == true)
			return true;
		return false;
	}

	/* ------------------------------------------------------------------ */

	void mark_final()
	{
		m_final = true;
	}

};

/* -------------------------------------------------------------------------- */

class translator
{
private:
	std::vector<state> m_states;
	int m_initial;

public:
	translator(std::string filename)
	{
		int no_states, no_roads, no_final, initial, current, id;
		char letter;

		std::string replace;
		// std::vector<char> alphabet;

		std::ifstream file;
		// set the file so it throws exception on errors
		file.exceptions(std::ifstream::failbit |
		                std::ifstream::badbit);

		try
		{
			file.open(filename);

			// read total number of states
			file>>no_states;

			// read the id for the initial state
			file>>initial;
			m_initial = initial;

			// read details about each state
			for(int i = 0; i < no_states; i++)
			{
				// add a new state
				state st(i);
				m_states.push_back(st);

				file>>no_roads;

				while(no_roads > 0)
				{
					file>>letter>>replace>>id;

					if(id > no_states)
						throw std::out_of_range
						("A road wants to go to a state that's not in the FST.");

//				if(std::find(alphabet.begin(),
//				             alphabet.end(),
//				             letter)
//				             != alphabet.end())
//					throw std::out_of_range
//				("A road uses a letter that's not in the alphabet");
					m_states[i].add_road(letter, replace, id);
					no_roads--;
				}
			}

			// read number of final states
			file>>no_final;

			// read all final states and mark each one
			while(no_final > 0)
			{
				file>>current;

				m_states[current].mark_final();

				no_final--;
			}

			// don't use more space than it's needed
			m_states.shrink_to_fit();

		}
		catch(std::ifstream::failure e)
		{
			std::cout<<"Error opening/reading the given file."
			         <<std::endl;
			std::cout<<e.what()<<std::endl;

			throw; // pass the exception
		}
		catch(...)
		{
			std::cout<<"There is a logic error in the given file."
			         <<std::endl;
			throw;
		}

	}

	/* ------------------------------------------------------------------ */

	int initial()
	{
		return m_initial;
	}

	/* ------------------------------------------------------------------ */

	void test_word(int state_id, std::string word, std::string result)
	{
		if(word.length() == 0)
		{
			if(m_states[state_id].is_final() == true)
			{
				std::cout<<"Found: "<<result<<std::endl;
			}
			else
			{
				// make sure we keep going on epsilon roads
				// AKA make sure we still add stuff at the end
				for(auto&& road : m_states[state_id].roads)
					if(road.letter() == epsilon)
						test_word(road.to(),
						          word,
						          result + road.replace());
			}
		}

		for(auto&& road : m_states[state_id].roads)
		{
			if(road.letter() == word.front())
				test_word(road.to(),
				          word.substr(1),
				          result + road.replace());
			else
				if(road.letter() == epsilon)
					test_word(road.to(),
					          word,
					          result + road.replace());
		}

		return;
	}
};

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

int main(int argc, char const *argv[])
{
	int again;
	bool done = false;
	translator *fst = nullptr;

//    if (argc != 2)
//    {
//        std::cout<<"Usage "<<argv[0]<<" file"<<std::endl;
//
//        return EXIT_FAILURE;
//    }

	try
	{
		// fst = new translator(argv[1]);
		fst = new translator("input.txt");
	}
	catch(const std::exception &e)
	{
		std::cout<<"Building the FST failed, with the following error: "
		         <<e.what()<<std::endl;
		return EXIT_FAILURE;
	}

	do
	{
		std::string word;

		std::cout<<"What word would you like to test?"<<std::endl;
		std::cin>>word;

		std::cout<<std::endl;
		fst->test_word(fst->initial(), word, "");

		std::cout<<std::endl;
		std::cout<<"Press 1 to test another word or 0 to exit."
		         <<std::endl;
		std::cin>>again;

		if(again == 0)
			done = true;

	}while(done == false);

	if(fst)
		delete fst;

	return EXIT_SUCCESS;
}
