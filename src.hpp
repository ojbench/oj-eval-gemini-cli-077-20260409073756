#ifndef SRC_HPP
#define SRC_HPP

namespace sjtu {
    class CrossArray{
    private:
        int max_lines;
        int current_lines;
        int** arrays;
        int* sizes;

    public:
        explicit CrossArray(int lines) {
            max_lines = lines;
            current_lines = 0;
            arrays = new int*[max_lines];
            sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                arrays[i] = nullptr;
                sizes[i] = 0;
            }
        }

        CrossArray(const CrossArray & o) {
            max_lines = o.max_lines;
            current_lines = o.current_lines;
            arrays = new int*[max_lines];
            sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                sizes[i] = o.sizes[i];
                if (o.arrays[i] != nullptr) {
                    arrays[i] = new int[sizes[i]];
                    for (int j = 0; j < sizes[i]; ++j) {
                        arrays[i][j] = o.arrays[i][j];
                    }
                } else {
                    arrays[i] = nullptr;
                }
            }
        }

        CrossArray & WhichGreater(CrossArray & o) {
            int count1 = 0;
            for (int i = 0; i < current_lines; ++i) {
                count1 += sizes[i];
            }
            int count2 = 0;
            for (int i = 0; i < o.current_lines; ++i) {
                count2 += o.sizes[i];
            }
            if (count1 >= count2) {
                return *this;
            } else {
                return o;
            }
        }

        bool IsSame(const CrossArray & o) {
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size) {
            if (current_lines >= max_lines) {
                return false;
            }
            if (size > 0) {
                arrays[current_lines] = new int[size];
                for (int i = 0; i < size; ++i) {
                    arrays[current_lines][i] = Input[i];
                }
            } else {
                arrays[current_lines] = nullptr;
            }
            sizes[current_lines] = size;
            current_lines++;
            return true;
        }

        void AppendArrays(const int * Input, int Line, int size) {
            if (size <= 0) return;
            int old_size = sizes[Line];
            int new_size = old_size + size;
            int* new_array = new int[new_size];
            for (int i = 0; i < old_size; ++i) {
                new_array[i] = arrays[Line][i];
            }
            for (int i = 0; i < size; ++i) {
                new_array[old_size + i] = Input[i];
            }
            if (arrays[Line] != nullptr) {
                delete[] arrays[Line];
            }
            arrays[Line] = new_array;
            sizes[Line] = new_size;
        }

        void DoubleCrossLength() {
            int new_max_lines = max_lines * 2;
            int** new_arrays = new int*[new_max_lines];
            int* new_sizes = new int[new_max_lines];
            for (int i = 0; i < max_lines; ++i) {
                new_arrays[i] = arrays[i];
                new_sizes[i] = sizes[i];
            }
            for (int i = max_lines; i < new_max_lines; ++i) {
                new_arrays[i] = nullptr;
                new_sizes[i] = 0;
            }
            delete[] arrays;
            delete[] sizes;
            arrays = new_arrays;
            sizes = new_sizes;
            max_lines = new_max_lines;
        }

        const int * AtArray(int i) {
            if (i < 0 || i >= max_lines) return nullptr;
            return arrays[i];
        }

        int & At(int i , int j) {
            return arrays[i][j];
        }

        ~CrossArray() {
            for (int i = 0; i < max_lines; ++i) {
                if (arrays[i] != nullptr) {
                    delete[] arrays[i];
                }
            }
            delete[] arrays;
            delete[] sizes;
        }
    };
}

#endif
