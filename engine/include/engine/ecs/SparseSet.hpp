#pragma once

#include "engine/ecs/EntitySet.hpp"

namespace engine::ecs {

template <typename T, std::size_t N = MAX_ENTITIES>
class SparseSet : public EntitySet<N> {
public:
  using Base = EntitySet<N>;
  using Base::contains;
  using Base::INVALID_INDEX;
  using Base::mCurrentSize;
  using Base::mDenseVector;
  using Base::mSparseArray;

  SparseSet() { mDataVector.reserve(MAX_ENTITIES); }

  void insert(Entity entity, T const &dataPoint) {
    assert(entity < MAX_ENTITIES &&
           "Given entity is greater than SparseSet array size");
    Base::insert(entity);
    mDataVector.push_back(dataPoint);
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
      mDataVector[removedIndex] = mDataVector[lastIndex];
    }
    mSparseArray[entity] = INVALID_INDEX;
    mDenseVector.pop_back();
    mDataVector.pop_back();
    mCurrentSize--;
    // print();
  }

  T &getData(Entity entity) {
    assert(contains(entity) &&
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
  std::vector<T> mDataVector;
};

} // namespace engine::ecs
