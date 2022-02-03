#include "game.h"
#include "deck.h"
#include <memory>

int main(int argc, char **argv) {
  unsigned seed_;
  std::string seed;
  if ( argc > 1 ) {
		try {
			seed_ = std::stoi( std::string{ argv[1] } );
      seed =  argv[1] ;
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	}
  std::shared_ptr<Game> g = std::make_shared<Game>();
  g->gameDeckGeneration();
  g->shuffle(seed);
  g->playerGeneration();
  if (g->play()) g->tell_winners();
}
