#include <iostream>

#include <utilities.hpp>

using namespace ASWL;

int TestNamespaceUtilities() {

	util::Logger("Hello World", true);

	std::string error = "xxxxx";
	std::string passArgs[] = { "Hello ", "World, @ [", "Andrew", "]." };
	util::Logger(error, std::string("ss"), passArgs[0], passArgs[1], passArgs[2], passArgs[3]);
	util::Logger('\n', false);
	util::Logger(error.c_str(), "ss");

	std::vector<std::string> rt = util::split("\nHello World! 22223,232,1212", ',');

	for (std::string r : rt)
		std::cout << r << " ";

	std::cout << '\n' << util::GetDateTime() << " -> " << util::GetDateTime("ctd") << std::endl;

	util::DeltaTime dt1;

	for (int x = 0; x < 10; x++) {
		std::cout << x << " " << dt1.GetDeltaTime() << std::endl;
		dt1.UpdateDeltaTime();
	}

	std::cout << std::endl;

	double tFPS = 0;
	util::DeltaTime dt2;

	int x = 0;
	dt2.UpdateDeltaTime(true);
	for (x = 0; x < 10000000; x++) {
		util::FramesPerSecond::UpdateFPS();
		std::cout << "";
		tFPS += util::FramesPerSecond::GetFPS();
	}
	dt2.UpdateDeltaTime();

	std::cout << x << " -- " << dt2.GetDeltaTime() << " ----- " << tFPS / 10000000 << std::endl;

	std::ifstream fileExists("file.txt");

	if (!fileExists) {
		std::ofstream file("log.OElog");
		file << "CREATED -> " << util::GetDateTime("ctd");
	}

	std::fstream file("file.txt", std::ios::out | std::ios::app);

	util::RedirectIOStream(std::ref(file), 1);
	util::Logger("RedirectIOStream test -> cerr", true);
	util::RedirectIOStream(std::ref(file), 6);
	util::Logger("UndirectIOStream test -> cerr", true);
	util::RedirectIOStream(std::ref(file), 1, true);
	util::RedirectIOStream(std::ref(file), 6);

	return 0;
}


int main() {

	int utiltest = TestNamespaceUtilities();

	if (utiltest == 0)
		std::cout << "\n-----------> Utilities Test Succeeded <-----------" << std::endl;

	return 0;
}
