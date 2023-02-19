#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <queue>

class Queue {

private:

	std::queue<std::string> the_queue_itself;

public:

	void AddToBack(std::string x) {
		the_queue_itself.push(x);
	}

	void RemoveFromQueue() {
		if ((!the_queue_itself.empty())) {
			the_queue_itself.pop();
		}
	}

	void ClearQueue() {
		while (!the_queue_itself.empty()) {
			the_queue_itself.pop();
		}
	}

	void AddToFront(std::string x) {
		std::queue<std::string> copy_queue = the_queue_itself;
		while (!the_queue_itself.empty()) {
			the_queue_itself.pop();
		}
		the_queue_itself.push(x);
		while (!copy_queue.empty()) {
			the_queue_itself.push(copy_queue.front());
			copy_queue.pop();
		}
	}

	std::string GetFirst() {
		return the_queue_itself.front();
	}

	bool IsEmpty() {
		return the_queue_itself.empty();
	}

	// Tomas	
	void OutputQueue() {
		system("clear");

		std::queue<std::string> copy_queue = the_queue_itself;

		if (copy_queue.empty()) {
			std::cout << "Your playlist is empty" << std::endl;
		} else {
			std::cout << "Your playlist is: " << std::endl;
			
			while (!copy_queue.empty()) {
				if (copy_queue.size() > 1){
					std::cout << copy_queue.front() << " " << std::endl;

				}
				else {
					std::cout << copy_queue.front() << " ";
				}
				copy_queue.pop();
			}
			std::cout << std::endl;
		 }

	}
};

class Player {

public:

	Player() : sound(buffer) {}
	
	void Play() {
		if (buffer.getSampleCount() == 0) {
			LoadAndPlay();
		} else {
			sound.play();
		}
	}

	void Pause() {
		sound.pause();
	}

	void Next() {
		if (playlist.IsEmpty()) {
			error = "Empty song queue";
			sound.stop();
		} else {
			LoadAndPlay();
		}
	}

	bool Run() {
		error = "";

		DrawMenu();

		// Alex -->
		std::cout << "Command: ";
		std::cin >> command;

		if (command == 'a') {
			AddNewSontToPlaylist(false);
		} else if (command == 'b') {
			AddNewSontToPlaylist(true);
		} else if (command == 'q') {
			playlist.OutputQueue();
		} else if (command == 'r') {
			playlist.RemoveFromQueue();
			playlist.OutputQueue();
		} else if (command == 'c') {
			playlist.ClearQueue();
			playlist.OutputQueue();
		} else if (command == 'p') {
			Play();
			Draw();
		} else if (command == 's') {
			Pause();
			Draw();
		} else if (command == 'n') {
			Next();
			Draw();
		} else if (command == 'x') {
			return false;
		}
		// <-- Alex

		return true;
	}

private:
	
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string error;
	std::string current_song;
	Queue playlist;
	char command;

	void Draw() {
		system("clear");

		if (error.empty()) {
			std::cout << "Current song: " << current_song << std::endl;
		} else {
			std::cout << error << std::endl;
		}
	}

	void DrawMenu() {
		std::cout << "-------------------------" << std::endl;
		std::cout << "Please select an action" << std::endl;
		std::cout << "\033[1;31ma\033[0m: Add song to the back" << std::endl;
		std::cout << "\033[1;31mb\033[0m: Add song to the front" << std::endl;
		std::cout << "\033[1;31mq\033[0m: Show all songs" << std::endl;
		std::cout << "\033[1;31mr\033[0m: Remove first song from the playlist" << std::endl;
		std::cout << "\033[1;31mc\033[0m: Clear playlist" << std::endl;
		std::cout << "\033[1;31mp\033[0m: Play song" << std::endl;
		std::cout << "\033[1;31ms\033[0m: Stop song" << std::endl;
		std::cout << "\033[1;31mn\033[0m: Next song" << std::endl;
		std::cout << "\033[1;31mx\033[0m: Quit" << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	// Alex
	void AddNewSontToPlaylist(bool is_front) {
		system("clear");

		std::string song;

		std::cout << "Enter the name of a song: ";
		std::cin >> song;

		if (is_front) {
			playlist.AddToFront(song);
		} else {
			playlist.AddToBack(song);
		}

		playlist.OutputQueue();
	}

	void LoadAndPlay() {
		if (playlist.IsEmpty()) {
			error = "Empty song queue";
		} else {
			current_song = playlist.GetFirst();

			playlist.RemoveFromQueue();

			if (buffer.loadFromFile(current_song)) {
				sound.play();
			} else {
				error = "Can't load song";
			}
		}
	}

};

int main() {

	Player player;

	while (true) {
		if (!player.Run()) {
			break;
		}
	}
	
	return 0;

}
