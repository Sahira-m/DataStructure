#include <iostream>
//#include <iomanip>
#include <map>
#include <limits>

template<typename K, typename V>
class interval_map {
    std::map<K,V> m_map;

public:
  // constructor associates whole range of K with val by inserting (K_min, val)
  // into the map
  interval_map( V const& val) {
      m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
  }

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  // implementation of assign function
  void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        // body of assign() function
       
        if (keyBegin < keyEnd)
        {
        std::pair<K,V> beginExtra;
        std::pair<K,V> endExtra;
        //bool valueAlreadyExist =false;
        //std::cout << "beginExtra   first        "<<beginExtra.first<<"  second   "<<beginExtra.second<< "keyb "<<keyBegin << "keye "<<keyEnd<<"\n";
        
        //std::cout << "Endextra      first    "<<endExtra.first<<"  second   "<<endExtra.second<<"\n";
        bool beginHasExtra = false;
        bool endHasExtra = false;
// open range for iterator
        typename std::map<K,V>::iterator itBegin = m_map.lower_bound(keyBegin);
        //std::cout << "it begin value is before  "<<itBegin->first;
        //itBegin = m_map.lower_bound(keyBegin);
        //bool p = itBegin != m_map.end();
        //std::cout << "NEW" << p;
        //if (itBegin != m_map.end() &&  keyBegin < itBegin->first ) {
        if (  keyBegin < itBegin->first ) {
           // std::cout << "beginfirst  " <<itBegin->first <<" beginsecond " <<val <<"  Key begin "<<keyBegin <<"\n  ";
            if (itBegin != m_map.begin()) {
                beginHasExtra = true;
                --itBegin;
                beginExtra = std::make_pair(itBegin->first, itBegin->second);
                std::cout << "\n open iterator \n";
               // std::cout << "beginfirst  " << itBegin->first << " beginsecond " << itBegin->second << "  Key begin " << keyBegin << "\n  ";
                std::cout << "  \n begin Extra  " << beginExtra.second << " Output \n";

            }
            
        }
// close range for iterator
        typename std::map<K,V>::iterator itEnd = m_map.lower_bound(keyEnd);;
       
        /* std::cout << "it begin key is "<<itEnd->first <<"\n";
        std::cout << "it begin value  is "<< itEnd->second<<"\n"; */
        //m_map.lower_bound(keyEnd)->second<<"\n";
         //if ( itEnd!=m_map.end() && keyEnd < itEnd->first ) {
        if (!(  keyEnd < itEnd->first )) {
            endHasExtra = true;//IPPO MATTY
            typename std::map<K,V>::iterator extraIt = itEnd;
            --extraIt;
            endExtra = std::make_pair(keyEnd, extraIt->second);
               std::cout << "\n close iterator \n";
            ///std::cout << "beginfirst last  " <<keyEnd <<" beginsecond last  " <<extraIt->second <<"\n  ";
            //std::cout << "\n end   extra " << endExtra.second<<"           OUTPUT\n";
            

        }

        // four canonical conflicts 
        bool insertMiddle = true;
        if (beginHasExtra) {
            if (beginExtra.second == val)
            {
                std::cout << " Bool 1" << beginExtra.second << " "<<val;
                insertMiddle = false;
                //endHasExtra = false;
                //beginHasExtra = false;
            }    
        } else {
            if (itBegin != m_map.begin()) {
                typename std::map<K,V>::iterator beforeMid = itBegin;
                --beforeMid;
                if (beforeMid->second == val)
                {
                    std::cout << " Bool 2" << beforeMid->second << " "<<val;
                    insertMiddle = false;
                    //endHasExtra = false;
                     //beginHasExtra = false;
                }    
            }
        }

//hiden 
          if (endHasExtra) {
            if ( (insertMiddle && endExtra.second == val) || (!insertMiddle && endExtra.second == beginExtra.second) )
            {
               // insertMid = false;
                    endHasExtra = false;
                    // beginHasExtra = false;
            }
                //endHasExtra = false;
        } else {
      
            if ( (insertMiddle && itEnd!=m_map.end() && itEnd->second == val) || (!insertMiddle && itEnd!=m_map.end() && itEnd->second == beginExtra.second) )
            {
                itEnd = m_map.erase(itEnd);
            std::cout << "PANDARAM";
            }
        }
  
       
        itBegin = m_map.erase(itBegin, itEnd);
        //std::cout << "\n      Replace begin" << itBegin->second << "     end     " << itEnd->second << " is ";
        if (beginHasExtra && beginExtra.second!=itBegin->second)
            {
                std::cout << " begin has extra";
                // std::cout << "Value already exist is " << valueAlreadyExist <<"\n  ";
                 std::cout << "  \n begin Extra  " << beginExtra.second << " Output \n";

                itBegin = m_map.insert(itBegin, beginExtra);
            }    
        if (insertMiddle && val!=itBegin->second)
        {
            std::cout << " mid insert";
            //std::cout << "Value already exist is " << valueAlreadyExist <<"\n  ";
            itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));
             std::cout << "  \n  mid insert"<< val<<" Output \n";

        }
        if (endHasExtra && val!=endExtra.second )
        {
            std::cout << " end has extra";
            //std::cout << "Value already exist is " << valueAlreadyExist <<"\n  ";
            m_map.insert(itBegin, endExtra);
            std::cout << "  \n end  Extra  " << endExtra.second << " Output \n";
        }
        }

 
     
        else
        {
            return;
        }
}
// return the value associated witk key
V const& operator[]( K const& key ) const 
    {
      return ( --m_map.upper_bound(key) )->second;
    } 
 

};
// main function to start the execution
int main()
{
    // instance of interval_map class
    interval_map<int,char> m('A');
    // calling of assign() function  
    m.assign(0, 1, 'B');
    m.assign(1, 2, 'B');
    //m.assign(2 ,3,'C');
    //m.assign(3, 4, 'D');
    //m.assign(4, 5, 'E');
    //m.assign(3, 4, 'J');
    // loop for maping key and its corresponding value
    for (int i = -1; i <=1; ++i)
        std::cout << '\n' << i << ' ' << m[i] ;
}