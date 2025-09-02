#pragma once

#include "engine/ecs/Entity.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <print>
#include <vector>

namespace engine::ecs {

template <typename T, std::size_t N = MAX_ENTITIES> class SparseSet {
public:
  SparseSet() {
    mCurrentSize = 0;
    mSparseArray.fill(INVALID_INDEX);
    mDenseVector.reserve(MAX_ENTITIES);
    mDataVector.reserve(MAX_ENTITIES);
  }

  void add(Entity entity, T const &dataPoint) {
    assert(entity < MAX_ENTITIES &&
           "Given entity is greater than SparseSet array size");
    mDenseVector.push_back(entity);
    mDataVector.push_back(dataPoint);
    mSparseArray[entity] = mCurrentSize;
    mCurrentSize++;
    // print();
  }

  void remove(Entity entity) {
    assert(mSparseArray[entity] != INVALID_INDEX &&
           "Entity is not attached to the SparseSet");
    std::size_t removedIndex = mSparseArray[entity];
    std::size_t lastIndex = mCurrentSize - 1;
    if (removedIndex != lastIndex) {
      Entity lastId = mDenseVector[lastIndex];
      mSparseArray[lastId] = removedIndex;
      mDenseVector[removedIndex] = lastId;
      mDataVector[removedIndex] = mDataVector[lastIndex];
    }
    mSparseArray[entity] = INVALID_INDEX;
    mDataVector.pop_back();
    mDenseVector.pop_back();
    mCurrentSize--;
    // print();
  }

  std::vector<Entity> &getDenseArray() { return mDenseVector; }
  std::array<std::size_t, N> getSparseArray() { return mSparseArray; }

  std::size_t getCurrentSize() { return mCurrentSize; }

  T &getData(Entity entity) {
    assert(mSparseArray[entity] != INVALID_INDEX &&
           "Entity is not attached to the SparseSet Data vector");
    std::size_t index = mSparseArray[entity];
    return mDataVector[index];
  }

  void print() {
    std::print("mDataVector : [ ");
    for (auto const &d : mDataVector) {
      std::print("{} ", d);
    }
    std::println("]");

    std::print("mDenseVector : [ ");
    for (auto const &e : mDenseVector) {
      std::print("{} ", e);
    }
    std::println("]");

    std::print("mSparseArray : [ ");
    for (std::size_t i = 0; i < mSparseArray.size(); ++i) {
      if (mSparseArray[i] == INVALID_INDEX)
        std::print("X ");
      else
        std::print("{} ", mSparseArray[i]);
    }
    std::println("]");
    std::println("mCurrentSize : {} ", mCurrentSize);
    std::println("===========================");
  }

private:
  static constexpr std::size_t INVALID_INDEX =
      std::numeric_limits<std::size_t>::max();
  std::size_t mCurrentSize;
  std::vector<T> mDataVector;
  std::vector<Entity> mDenseVector;
  std::array<std::size_t, N> mSparseArray{};
};

} // namespace engine::ecs
