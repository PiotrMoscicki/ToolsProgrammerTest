#include "Application/Application.hpp"

int main(int argc, char **argv)
{
	TPT::Application a(argc, argv);
	return a.exec();
}