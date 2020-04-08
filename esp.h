#include <vector>
#include <map>
#include <utility>


class ESPCalc
{

  private:
    std::vector<double> m_roots; 
    int m_size; 

    std::map< std::pair<int, int>, std::vector< std::vector<int> > > m_index_cache;


  public:
    ESPCalc(std::vector<double> roots) : m_roots(roots) { m_size = m_roots.size();}

    double calc_esp_k(int k);
    std::vector<double> calc_esp_list();

    // Made public as this could be used outside the class  
    std::vector< std::vector<int> > calculate_indices(int size, int k);


};

/******
std::vector< std::vector<int> > calculate_indices(int size, int k);


double calculate_esp(std::vector<double> roots, int k){

  if(k==0) return 1;

  int size = roots.size();
  std::vector< std::vector<int> > indices = calculate_indices(size, k);

  double sum=0;
  for(auto group : indices){
    double product = 1;
    for(auto index : group){
      product *= roots.at(index);
    }
    sum += product;
  }
  return sum;

}

// TODO implement caching 
std::vector< std::vector<int> > calculate_indices(int size, int k){
  
  if(k==0 || k>size){
    throw std::invalid_argument("e_k is only defined for k <= N");
  }

  std::vector<std::vector<int>> indices;
  if(k==1){
    for(int x=0; x<size; ++x){
      std::vector<int> temp = {x};
      indices.push_back(temp);
    }
    return indices;
  }
  else if(k>1){
    
    indices = calculate_indices(size, k-1);

    std::vector< std::vector<int> > new_indices;
    for(auto tup : indices){
      for(int i=tup.back()+1; i<size; ++i){
        std::vector<int> new_tup = tup;
        new_tup.push_back(i);
        new_indices.push_back(new_tup);
      }
    }
    return new_indices;
  }
}
***********/

