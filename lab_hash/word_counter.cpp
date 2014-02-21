/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq( const string & infile ) : filename( infile ) { /* nothing */ }

template <template <class K, class V> class HT>
vector< pair<string, int> > WordFreq<HT>::getWords( int threshold ) const {
	TextFile infile( filename );
	vector< pair<string, int> > ret;
    	
    	HT<string,int> ht(256);
    	
    	while ( infile.good() ) {
    		string theWord = infile.getNextWord();
    		ht[theWord]++;
    	}
    	
    	typename HT<string,int>::iterator iter;
    	
    	for (iter = ht.begin(); iter != ht.end(); iter++) {
    		
    		if ( (iter->second) >= threshold ) ret.push_back(*iter);
    	
    	}
    
	return ret;
}
