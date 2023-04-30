#include "global.h"
#include "App.h"

#define TEST //FOR CODING
#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// Run unit tests

// Model

// Persistence

#include "../Persistence/Persistence.h"
#include "../Model/GameModel.h"

TEST_CASE("1", "Sikeres beolvasás")
{
    auto p = new Persistence();

    try
    {
        auto _fields = list<Field*>();
        auto _fin_state = finantial_state{0,0,0,0,0};
        p->readGameState("tests/persistence_readtest1.txt", _fields, _fin_state);
        //CHECK _fields ans _finstate
        // for (auto f : _fields)
        // {
        //     if (f != nullptr)
        //     {
        //         cout << f->toString() << endl;
        //     }
        // }
        cout << _fin_state.toString() << endl;
    }
    catch(IOException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

TEST_CASE("2", "Sikertelen beolvasás")
{
    auto p = new Persistence();
    auto _fields = list<Field*>();
    auto _fin_state = finantial_state{0,0,0,0,0};
    CHECK_THROWS(p->readGameState("NO_SUCH.FILE", _fields, _fin_state));

}

TEST_CASE("3", "Kiiras")
{
    //
}

#else // TEST
    
//Run main program
int main()
{
    App* _app = App::Instance();
    _app->Run();
    //Here we can handle things that should happen after the game is closed

}

#endif // TEST
