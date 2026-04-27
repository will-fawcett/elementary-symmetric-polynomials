#include "esp.h"

std::vector<double> ESPCalc::calc_esp_list(){

  std::vector<double> esp_list;
  esp_list.reserve(m_size + 1);
  for(int i=0; i<=m_size; ++i){
    esp_list.push_back( calc_esp_k(i) );
  }

  return esp_list;

}

/**
 * @brief calculate e_k, the kth symmetric polynomial
 * @param k The order of the polynomial
 */
double ESPCalc::calc_esp_k(int k){

  if(k<0) throw std::invalid_argument("e_k is not defined for k < 0");
  if(k==0) return 1;

  const std::vector< std::vector<int> >& indices = calculate_indices(m_size, k);

  double sum=0;
  for(const auto& group : indices){
    double product = 1;
    for(int index : group){
      product *= m_roots.at(index);
    }
    sum += product;
  }
  return sum;
}


/**
 * @brief Calculates the set of groups of indices that are required to produce the kth symmetric polynomial. To calculate the ESP, the values corresponding to each index in each group are multiplied together, and then each group is summed together. This function only returns the groups of indices.
 * @param size The number of elements in the polynomial
 * @param k The order of the polynomial
 */
std::vector< std::vector<int> > ESPCalc::calculate_indices(int size, int k){

  if(k<0){
    throw std::invalid_argument("e_k is not defined for k < 0");
  }
  if(k>size){
    throw std::invalid_argument("e_k is only defined for k <= N");
  }

  auto cached = m_index_cache.find(k);
  if(cached != m_index_cache.end()){
    return cached->second;
  }

  // Build levels iteratively from the largest cached level up to k.
  // Level 0 is the single empty group, representing the empty product.
  int start_level = 0;
  std::vector< std::vector<int> > indices{ std::vector<int>{} };
  for(int level=k; level>=0; --level){
    auto hit = m_index_cache.find(level);
    if(hit != m_index_cache.end()){
      indices = hit->second;
      start_level = level;
      break;
    }
  }
  if(start_level == 0 && m_index_cache.find(0) == m_index_cache.end()){
    m_index_cache[0] = indices;
  }

  for(int level=start_level+1; level<=k; ++level){
    std::vector< std::vector<int> > next;
    for(const auto& tup : indices){
      int begin = tup.empty() ? 0 : tup.back()+1;
      for(int i=begin; i<size; ++i){
        std::vector<int> new_tup = tup;
        new_tup.push_back(i);
        next.push_back(new_tup);
      }
    }
    indices = std::move(next);
    m_index_cache[level] = indices;
  }

  return indices;
}
