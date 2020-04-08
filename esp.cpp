#include "esp.h"

std::vector<double> ESPCalc::calc_esp_list(){

  std::vector<double> esp_list;
  for(int i=0; i<m_size; ++i){
    esp_list.push_back( calc_esp_k(i) );
  }

  return esp_list;

}

/**
 * @brief calculate e_k, the kth symmetric polynomial
 * @param k The order of the polynomial
 */
double ESPCalc::calc_esp_k(int k){

  if(k==0) return 1;

  std::vector< std::vector<int> > indices = calculate_indices(m_size, k);

  double sum=0;
  for(auto group : indices){
    double product = 1;
    for(auto index : group){
      product *= m_roots.at(index);
    }
    sum += product;
  }
  return sum;
}


/**
 * @brief Calculates the set of groups of indices that are required to produce the kth symmetric polynomial. To calculate the ESP, each the value which correspond to each index in each group are multiplied together, and then each group is summed together. Although this function only returns the groups of indices.
 * @param size The number of elements in the polynomial
 * @param k The order of the polynomial
 */
std::vector< std::vector<int> > ESPCalc::calculate_indices(int size, int k){

  // check cache
  std::pair<int, int> key = std::make_pair(size, k);
  if(m_index_cache.find(key) != m_index_cache.end()){
    return m_index_cache[key];
  }

  std::vector<std::vector<int>> indices;
  
  if(k>size){
    throw std::invalid_argument("e_k is only defined for k <= N");
  }
  else if(k==1){
    for(int x=0; x<size; ++x){
      std::vector<int> temp = {x};
      indices.push_back(temp);
    }
  }
  else if(k>1){
    std::vector< std::vector<int> > old_indices = calculate_indices(size, k-1);
    for(auto tup : old_indices){
      for(int i=tup.back()+1; i<size; ++i){
        std::vector<int> new_tup = tup;
        new_tup.push_back(i);
        indices.push_back(new_tup);
      }
    }
  }
  else{
    throw std::invalid_argument("Indices defined for k=0");
  }

  // store in cache
  m_index_cache[key] = indices;

  return indices;
}
