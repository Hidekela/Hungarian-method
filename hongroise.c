#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Math utils
int min(int a, int b);
int max(int a, int b);
int min_i(int **T, int i, size_t col_size);
int min_j(int **T, int j, size_t row_size, size_t col_size);
bool in(int a, int *L, size_t size);
bool in_char(char a, char *L, size_t size);
int count_L(int a, int *L, size_t size);
int count_L_char(char a, char *L, size_t size);
int minpos_L_index(int *L, size_t size);
int get_L_index(char a, char *L, size_t size);
int get_Lj_char_index(char a, int j, char **N, size_t row_size, size_t col_size);
void transpose_nxn(int **T, size_t row_size, size_t col_size);
void transpose_nxn_char(char **N, size_t row_size, size_t col_size);

// Program utils
void zero_L(int *L, size_t size);
void copy_L(int *L, int *N, size_t size);
void copy_tab(int **T, size_t Trow_size, size_t Tcol_size, int **C, size_t Crow_size, size_t Ccol_size);
void print_tab(int **T, size_t row_size, size_t col_size);
void print_tab_char(char **N, size_t row_size, size_t col_size);

// Algo utils
int max_tab(int **T, size_t row_size, size_t col_size);
void create_tab_EB(int **T, char **N, size_t row_size, size_t col_size);
bool in_tab(char c, int **N, size_t row_size, size_t col_size);
int min_tab(int **T, size_t row_size, size_t col_size, int *Lnotstroke, int *Cstroke);
int compute_final_min(int **T, char **N, size_t row_size, size_t col_size, bool n_gt_p);

// UI utils
void print_tab_marked(char **N, int *L, int *C, size_t row_size, size_t col_size);
void print_tab_stroke(int **T, int *Lnotstroke, int *Cstroke, size_t row_size, size_t col_size);
void print_tab_final(int **T, char **N, size_t row_size, size_t col_size, bool n_gt_p);


int main() {
    // --- Examples ---

    // Normal
    #define ROW_ 4
    #define COL_ 4
    int O[ROW_][COL_] = {{6,3,5,2}, {3,1,4,2}, {2,3,5,3}, {4,5,7,6}};

    // // With loop
    // #define ROW_ 5
    // #define COL_ 5
    // int O[ROW_][COL_] = {{8,7,5,6,4}, {2,5,2,5,4}, {1,4,2,3,1}, {2,6,2,4,4}, {2,4,1,3,4}};

    // // Loop transpose ?
    // #define ROW_ 5
    // #define COL_ 5
    // int O[ROW_][COL_] = {{8,7,5,6,4}, {2,5,2,5,4}, {1,4,2,3,1}, {2,6,2,4,4}, {2,4,1,3,4}};
    // transpose_nxn((int**) O, ROW_, COL_);
    // // Irrelevant

    // // Loop or what?
    // #define ROW_ 5
    // #define COL_ 5
    // int O[ROW_][COL_] = {{7,1,3,1,2}, {4,2,4,3,2}, {4,1,4,1,1}, {5,4,5,3,3}, {1,1,1,1,2}};
    // // Nope, and it works. And its transpose?
    // transpose_nxn((int**) O, ROW_, COL_);
    // // Same
    
    // // n > p
    // #define ROW_ 7
    // #define COL_ 4
    // int O[ROW_][COL_] = {{14,11,9,10}, {11,9,10,10}, {10,13,11,12}, {12,9,10,11}, {10,9,11,8}, {9,12,7,11}, {11,8,12,11}};

    // ----------------

    // case where n > p
    #define ROW ROW_
    #if (ROW_ > COL_)
        #define COL COL_ + 1
    #else
        #define COL COL_
    #endif

    int A[ROW][COL];
    copy_tab((int**) O, ROW_, COL_, (int**) A, ROW, COL);

    if (ROW_ > COL_) {
        int a = max_tab((int**) A, ROW_, COL_) + 1;
        for (int i = 0; i < ROW; i++) {
            A[i][COL_] = a;
        }
    }

    // Loop prevent
    bool transposed = false;
    int L_prev[ROW], C_prev[COL];
    zero_L(L_prev, ROW);
    zero_L(C_prev, COL);

    // UI
    puts("--- Methode Hongroise ---");
    print_tab((int**) A, ROW, COL);

    // 1st step
    puts("1ere etape:");
    for (int i = 0; i < ROW; i++) {
        int m = min_i((int**) A, i, COL);
        if (m == 0) continue;
        for (int j = 0; j < COL; j++)
            A[i][j] -= m;
    }
    print_tab((int**) A, ROW, COL);
    for (int j = 0; j < COL; j++) {
        int m = min_j((int**) A, j, ROW, COL);
        if (m == 0) continue;
        for (int i = 0; i < ROW; i++) 
            A[i][j] -= m;
    }
    print_tab((int**) A, ROW, COL);

    while (true) {    
        // 2nd step
        puts("2eme etape:");
        char Z[ROW][COL];
        create_tab_EB((int**) A, (char **) Z, ROW, COL);
        print_tab_char((char**) Z, ROW, COL);
        int L[ROW];
        zero_L(L, ROW);
        while (in_tab('0', (int**) Z, ROW, COL)) {
            for (int i = 0; i < ROW; i++) {
                L[i] = count_L_char('0', Z[i], COL);
            }
            int l = minpos_L_index(L, ROW);
            int c = get_L_index('0', Z[l], COL);
            // Frame the 0 on Z[l][c]
            Z[l][c] = 'E';
            print_tab_char((char**) Z, ROW, COL);
            // Stroke the other 0 on this row and column
            if (c == COL_) // on the column p+1
                continue;
            for (int j = 0; j < COL; j++) {
                if (Z[l][j] == '0')
                    Z[l][j] = 'B';
            }
            for (int i = 0; i < ROW; i++) {
                if (Z[i][c] == '0')
                    Z[i][c] = 'B';
            }
            print_tab_char((char**) Z, ROW, COL);
        }

        zero_L(L, ROW);
        for (int i = 0; i < ROW; i++) {
            if (!in_char('E', Z[i], COL))
                L[i] = 1; // 1 for marked // mangalatra manao step 3.a eto ;p de toute façon 3.a ne se répètera pas
        }
        
        if (!in(1, L, ROW)) {
            if (transposed)
                transpose_nxn_char((char**) Z, ROW, COL);
            int O_[ROW][COL], **F = (int**) O;
            if (ROW_ > COL_) {
                F = (int**) O_;
                copy_tab((int**) O, ROW_, COL_, (int**) O_, ROW, COL);
            }
            puts("Tableau final:");
            print_tab_final(F, (char**) Z, ROW, COL, ROW_ > COL_);
            printf("Cout minimal: %d\n", compute_final_min(F, (char**) Z, ROW, COL, ROW_ > COL_));
            return 0;
        }
        
        // 3rd step
        puts("3eme etape:");
        int C[COL];
        zero_L(C, COL);
        int Lmarked = count_L(1, L, ROW), Cmarked = 0, LCmarked_prev;
        print_tab_marked((char**) Z, L, C, ROW, COL);
        do {
            LCmarked_prev = Lmarked + Cmarked;
            // 3.b
            for (int i = 0; i < ROW; i++) {
                if (L[i] != 1)
                    continue;
                for (int j = 0; j < COL; j++) {
                    if (Z[i][j] == 'B' && C[j] != 1) {
                        C[j] = 1;
                        Lmarked++;
                        print_tab_marked((char**) Z, L, C, ROW, COL);
                    }
                }
            }
            // 3.c
            for (int j = 0; j < COL; j++) {
                // 3.c_1
                if (C[j] != 1)
                    continue;
                int l = get_Lj_char_index('E', j, (char **) Z, ROW, COL);
                if (l == -1) return -1; // Error in the algo?
                if (L[l] == 1) // already marked
                    continue;
                // 3.c_2
                int l_ = 0; // = 0 for the case of no 0 stroked, cause we'll mark it
                for (int j_ = 0; j_ < COL; j_++) {
                    if (Z[l][j_] != 'B')
                        continue;
                    l_ = get_Lj_char_index('E', j_, (char **) Z, ROW, COL);
                    if (l_ == -1) {
                        // do not mark this row
                        break;
                    }
                }
                if (l_ != -1) {
                    L[l] = 1;
                    Cmarked++;
                    print_tab_marked((char**) Z, L, C, ROW, COL);
                }
            }
        } while (LCmarked_prev < Lmarked + Cmarked);

        // Detect loop // Can be put after step 4 too
        int k = 0;
        for (; k < COL; k++) {
            if (L[k] + L_prev[k] != 1 || C[k] + C_prev[k] != 1)
                break;
        }
        if (k == COL) { // There is loop
            transposed = !transposed;
            puts("Il y a une boucle ==> transposer");
            transpose_nxn((int**) A, ROW, COL);
            transpose_nxn_char((char**) Z, ROW, COL);
            print_tab((int**) A, ROW, COL);
            // update with switch
            zero_L(C_prev, ROW);
            zero_L(L_prev, COL);
            continue;
        }
        // update L_prev & C_prev for next test
        copy_L(L, L_prev, ROW);
        copy_L(C, C_prev, COL);

        // 4th step
        puts("4eme etape:");
        print_tab_stroke((int**) A, L, C, ROW, COL);

        int m = min_tab((int**) A, ROW, COL, L, C);
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (L[i] == 1 && C[j] == 0)
                    A[i][j] -= m;
                else if (L[i] == 0 && C[j] == 1)
                    A[i][j] += m;
            }
        }
        print_tab((int**) A, ROW, COL);
    }

    return 0;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return -min(-a, -b);
    return a >= b ? a : b;
}

int min_i(int **T, int i, size_t col_size) {
    int m = __INT_MAX__;
    int (*S)[col_size] = (int (*)[col_size]) T;
    
    for (int j = 0; j < col_size; j++) {
        m = min(m, S[i][j]);
    }
    return m;
}

int min_j(int **T, int j, size_t row_size, size_t col_size) {
    int m = __INT_MAX__;
    int (*S)[col_size] = (int (*)[col_size]) T;
    
    for (int i = 0; i < row_size; i++) {
        m = min(m, S[i][j]);
    }
    return m;
}

bool in(int a, int *L, size_t size) {
    for (int i = 0; i < size; i++) {
        if (a == L[i]) 
            return true;
    }
    return false;
}

bool in_char(char a, char *L, size_t size) {
    for (int i = 0; i < size; i++) {
        if (a == L[i]) 
            return true;
    }
    return false;
}

int count_L(int a, int *L, size_t size) {
    int c = 0;
    for (int i = 0; i < size; i++) {
        if (a == L[i])
            c++;
    }
    return c;
}

int count_L_char(char a, char *L, size_t size) {
    int c = 0;
    for (int i = 0; i < size; i++) {
        if (a == L[i])
            c++;
    }
    return c;
}

int minpos_L_index(int *L, size_t size) {
    int mi = -1;
    for (int i = 0; i < size; i++) {
        if (L[i] > 0) {
            mi = i;
            break;
        }
    }
    if (mi == -1)
        return -1;
    
    for (int i = mi + 1; i < size; i++) {
        mi = min(L[mi], L[i]) == L[mi] || L[i] < 1 ? mi : i;
    }
    return mi;
}

int get_L_index(char a, char *L, size_t size) {
    for (int i = 0; i < size; i++) {
        if (L[i] == a)
            return i;
    }
    return -1;
}

int get_Lj_char_index(char a, int j, char **N, size_t row_size, size_t col_size) {
    char (*M)[col_size] = (char (*)[col_size]) N;

    for (int i = 0; i < row_size; i++) {
        if (M[i][j] == a)
            return i;
    }
    return -1;
}

void copy_tab(int **T, size_t Trow_size, size_t Tcol_size, int **C, size_t Crow_size, size_t Ccol_size) {
    int (*S)[Tcol_size] = (int (*)[Tcol_size]) T;
    int (*N)[Ccol_size] = (int (*)[Ccol_size]) C;

    int row_size = min(Trow_size, Crow_size), col_size = min(Tcol_size, Ccol_size);

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++)
            N[i][j] = S[i][j];
    }
}

void transpose_nxn(int **T, size_t row_size, size_t col_size) {
    int (*S)[col_size] = (int (*)[col_size]) T;

    if (row_size != col_size)
        return;

    int s;
    for (int i = 0; i < row_size ; i++) {
        for (int j = 0; j < i ; j++) {
            s = S[j][i];
            S[j][i] = S[i][j];
            S[i][j] = s;
        }
    }
}

void transpose_nxn_char(char **N, size_t row_size, size_t col_size) {
    char (*M)[col_size] = (char (*)[col_size]) N;

    if (row_size != col_size)
        return;

    int m;
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < i; j++) {
            m = M[j][i];
            M[j][i] = M[i][j];
            M[i][j] = m;
        }
    }
}

void zero_L(int *L, size_t size) {
    for (int i = 0; i < size; i++) {
        L[i] = 0;
    }
}

void copy_L(int *L, int *N, size_t size) {
    for (int i = 0; i < size; i++) {
        N[i] = L[i];
    }
}

void print_tab(int **T, size_t row_size, size_t col_size) {
    int (*S)[col_size] = (int (*)[col_size]) T;

    printf("\n");
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++)
            printf("%d\t", S[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_tab_char(char **N, size_t row_size, size_t col_size) {
    char (*M)[col_size] = (char (*)[col_size]) N;

    printf("\n");
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++)
            printf("%c\t", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

int max_tab(int **T, size_t row_size, size_t col_size) {
    int m = 0;
    int (*S)[col_size] = (int (*)[col_size]) T;

    for (int i = 0; i < row_size; i++) {        
        for (int j = 0; j < col_size; j++) {
            m = max(m, S[i][j]);
        }
    }
    return m;
}

void create_tab_EB(int **T, char **N, size_t row_size, size_t col_size){
    int (*S)[col_size] = (int (*)[col_size]) T;
    char (*M)[col_size] = (char (*)[col_size]) N;

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            M[i][j] = S[i][j] == 0 ? '0' : '-';
        }
    }
}

bool in_tab(char c, int **N, size_t row_size, size_t col_size) {
    char (*M)[col_size] = (char (*)[col_size]) N;

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            if (M[i][j] == c)
                return true;
        }
    }
    return false;
}

int min_tab(int **T, size_t row_size, size_t col_size, int *Lnotstroke, int *Cstroke) {
    int m = __INT_MAX__;
    int (*S)[col_size] = (int (*)[col_size]) T;

    for (int i = 0; i < row_size; i++) {
        if (Lnotstroke[i] == 0)
            continue;
        
        for (int j = 0; j < col_size; j++) {
            if (Cstroke[j] == 1)
                continue;

            m = min(m, S[i][j]);
        }
    }
    return m;
}

int compute_final_min(int **T, char **N, size_t row_size, size_t col_size, bool n_gt_p) {
    int (*S)[col_size] = (int (*)[col_size]) T;
    char (*M)[col_size] = (char (*)[col_size]) N;

    int m = 0;

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++){
            if (M[i][j] != 'E')
                continue;
            if (n_gt_p && j == col_size - 1)
                continue;
            m += S[i][j];
        }
    }
    return m;
}

void print_tab_marked(char **N, int *L, int *C, size_t row_size, size_t col_size) {
    char (*S)[col_size] = (char (*)[col_size]) N;

    printf("\n");
    for (int j = 0; j < col_size; j++) {
        if (C[j] == 1)
            printf(" X \t");
        else
            printf("   \t");
    }
    printf("\n");
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++)
            printf(" %c \t", S[i][j]);
        if (L[i] == 1)
            printf("\tX");
        printf("\n");
    }
    printf("\n");
}

void print_tab_stroke(int **T, int *Lnotstroke, int *Cstroke, size_t row_size, size_t col_size) {
    int (*S)[col_size] = (int (*)[col_size]) T;

    printf("\n");
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++){
            if (Lnotstroke[i] == 0 || Cstroke[j] == 1)
                printf("%%%d%%\t", S[i][j]);
            else
                printf(" %d \t", S[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_tab_final(int **T, char **N, size_t row_size, size_t col_size, bool n_gt_p) {
    int (*S)[col_size] = (int (*)[col_size]) T;
    char (*M)[col_size] = (char (*)[col_size]) N;

    printf("\n");
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++){
            if (n_gt_p && j == col_size - 1)
                continue;
            if (M[i][j] == 'E')
                printf("|%d|\t", S[i][j]);
            else
                printf(" %d \t", S[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
