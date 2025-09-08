#pragma once
#include "engine/ecs/EntityManager.hpp"
#include <cassert>
#include <print>

namespace engine::ecs {

template <std::size_t N = MAX_ENTITIES> class EntitySet {
public:
  EntitySet() {
    mCurrentSize = 0;
    mSparseArray.fill(INVALID_INDEX);
    mDenseVector.reserve(MAX_ENTITIES);
  }

  void insert(Entity entity) {
    assert(entity < MAX_ENTITIES &&
           "Given entity is greater than EntitySet array size");
    assert(!contains(entity) && "Entity is already in the SparseSet");
    mDenseVector.push_back(entity);
    mSparseArray[entity] = mCurrentSize;
    mCurrentSize++;
    // print();
  }

  void remove(Entity entity) {
    if (!contains(entity))
      return;
    std::size_t removedIndex = mSparseArray[entity];
    std::size_t lastIndex = mCurrentSize - 1;
    if (removedIndex != lastIndex) {
      Entity lastId = mDenseVector[lastIndex];
      mSparseArray[lastId] = removedIndex;
      mDenseVector[removedIndex] = lastId;
    }
    mSparseArray[entity] = INVALID_INDEX;
    mDenseVector.pop_back();
    mCurrentSize--;
    // print();
  }

  std::vector<Entity> &getDenseArray() { return mDenseVector; }
  const std::vector<Entity> &getDenseArray() const { return mDenseVector; }

  std::array<std::size_t, N> &getSparseArray() { return mSparseArray; }
  const std::array<std::size_t, N> &getSparseArray() const {
    return mSparseArray;
  }

  bool contains(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity is out of bounds");
    return mSparseArray[entity] != INVALID_INDEX;
  }

  std::size_t getCurrentSize() { return mCurrentSize; }

  void print() {
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
  }

protected:
  static constexpr std::size_t INVALID_INDEX =
      std::numeric_limits<std::size_t>::max();
  std::size_t mCurrentSize;
  std::vector<Entity> mDenseVector;
  std::array<std::size_t, N> mSparseArray{};
};
} // namespace engine::ecs
