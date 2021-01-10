#include <iostream>

#include <utilities.hpp>
#include <logger.hpp>

using namespace ASWL;
namespace util = ASWL::Utilities;

int TestNamespaceUtilities() {

	Logger::logger("XXXXX", "Hello World!", true);

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

	std::fstream file("out.txt", std::ios::out | std::ios::app);
	Logger::SetLogStream(std::ref(file));
	Logger::logger("XXXXX", "Hello World!");

	return 0;
}


int main() {

	int utiltest = TestNamespaceUtilities();

	if (utiltest == 0)
		std::cout << "\n-----------> Utilities Test Succeeded <-----------" << std::endl;

	return 0;
}
