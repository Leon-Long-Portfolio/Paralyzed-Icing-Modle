#include <iostream>
#include <math.h>
#include <stack>
#include <cstdlib> // For rand()
#include <ctime>   // For srand()

using namespace std;

#define Lx  16
#define Ly  16
#define N  Lx*Ly
#define Three 3

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

inline int mod(int x, int n) {
    return  (n + (x % n)) % n;
}

inline int nn(int site, int mu) {
    int x, y;
    int xp, xm, yp, ym;
    int neighbor;

    x = site % Lx; y = site / Lx;
    xp = mod(x + 1, Lx); xm = mod(x - 1, Lx); yp = mod(y + 1, Ly); ym = mod(y - 1, Ly);

    switch (mu) {
    case 0:  neighbor =  xp + Lx * y; break; // positive
    case 1:  neighbor =  x + Lx * yp;  break;
    case 2:  neighbor =  xp + Lx * yp; break;

    case 3:  neighbor =  xm + Lx * y; break;  // negative
    case 4:  neighbor =  x + Lx * ym; break;
    case 5:  neighbor =  xm + Lx * ym; break;

    default: neighbor = -1;
    }
    return neighbor;
}

int FindGraph(int **frozen, int *spin, double *K);
int FindClusters(int *label, int **frozen, int *size);
void printArray(int *array);

void WolffUpdate(int *spin, double *K);
void SwendsenWangUpdate(int **frozen, int *spin, double *K);

int main() {

    int spin[N];
    double K[3];
    K[0] = 4.0;  K[1] = 4.0;  K[2] = 0.0;

    srand((unsigned int)time(nullptr)); // Seed random number generator

    // Initialize spins 
    for (int s1 = 0; s1 < N; s1++)
        spin[s1] = (rand() % 2 == 0) ? 1 : -1; // Random spin configuration

    // Percolation graph generation
    int **frozen = new int*[N];  // row count 
    for (int s = 0; s < N; ++s)
        frozen[s] = new int[6];   // column count

    FindGraph(frozen, spin, K);

    // Cluster identification
    int label[N];
    int size[N];
    int ClusterTotal;
    ClusterTotal = FindClusters(label, frozen, size);

    cout << "Spin array with N = " << N << endl;
    printArray(spin);
    cout << "Cluster Labels" << endl;
    printArray(label);
    int totSize = 0;
    cout << "Total Number of Clusters: " << ClusterTotal << endl;

    for (int i = 0; i < ClusterTotal; i++) {
        totSize += size[i];
        cout << "Cluster " << i << ": Size = " << size[i] << endl;
    }
    cout << "Total Cluster Size: " << totSize << endl;

    // Clean up
    for (int s = 0; s < N; ++s)
        delete[] frozen[s];
    delete[] frozen;

    return 0;
}

// Percolation graph generation
int FindGraph(int **frozen, int *spin, double *K) {
    for (int s1 = 0; s1 < N; s1++) {
        for (int mu = 0; mu < 3; mu++) {
            if (spin[nn(s1, mu)] == spin[s1] && (double)rand() / (double)RAND_MAX > exp(-2 * K[mu])) {
                frozen[s1][mu] = 1; frozen[nn(s1, mu)][mu + 3] = 1;
            }
            else {
                frozen[s1][mu] = 0; frozen[nn(s1, mu)][mu + 3] = 0;
            }
        }
    }
    return 0;
}

// Cluster identification (same as before)
int FindClusters(int *label, int **frozen, int *size) {
    for (int site = 0; site < N; site++) {
        label[site] = 0; size[site] = 0;
    }

    std::stack<int> stack;

    int seed = 0;
    int cluster_number = 0;

    while (seed < N) {
        cluster_number += 1;
        label[seed] = cluster_number;
        stack.push(seed);

        while (!stack.empty()) {
            int s_cluster = stack.top();
            stack.pop();
            size[cluster_number - 1] += 1;
            for (int mu = 0; mu < 6; mu++) {
                int site_mu = nn(s_cluster, mu);

                if ((frozen[s_cluster][mu] == 0) || (label[site_mu] > 0)) continue;  // already found

                label[site_mu] = cluster_number;
                stack.push(site_mu);
            }
        }
        while (label[seed] != 0) seed += 1;  // Get next cluster seed
    }
    return cluster_number;
}

// Print array helper function (same as before)
void printArray(int *lattice) {
    cout << "\n--------------------------------------------";
    for (int y = 0; y < Ly; y++) {
        cout << endl;
        for (int x = 0; x < Lx; x++)
            printf(" %4d", lattice[x + y * Lx]);
    }
    cout << "\n-------------------------------------------- \n";
}

// Wolff Update Algorithm
void WolffUpdate(int *spin, double *K) {
    double beta = 1.0 / K[0]; // Inverse temperature

    // Randomly choose a spin site
    int site = rand() % N;
    int spin_value = spin[site];

    // Perform Wolff cluster flipping
    std::stack<int> stack;
    stack.push(site);
    while (!stack.empty()) {
        int current_site = stack.top();
        stack.pop();

        // Flip the spin with a probability based on the interaction strength and current spin state
        if (spin[current_site] == spin_value && ((double)rand() / RAND_MAX) < (1.0 - exp(-2.0 * beta))) {
            spin[current_site] *= -1; // Flip the spin
            // Add neighboring sites with the same spin to the stack
            for (int mu = 0; mu < 6; mu++) {
                int neighbor = nn(current_site, mu);
                if (spin[neighbor] == spin_value) {
                    stack.push(neighbor);
                }
            }
        }
    }
}

// Swendsen-Wang Update Algorithm
void SwendsenWangUpdate(int **frozen, int *spin, double *K) {
  double beta = 1.0 / K[0]; // Inverse temperature

    // Generate bonds based on spin states and interaction strength
    for (int s1 = 0; s1 < N; s1++) {
        for (int mu = 0; mu < 3; mu++) {
            if (spin[nn(s1, mu)] == spin[s1] && ((double)rand() / RAND_MAX) < (1.0 - exp(-2.0 * beta))) {
                frozen[s1][mu] = 1; frozen[nn(s1, mu)][mu + 3] = 1;
            }
            else {
                frozen[s1][mu] = 0; frozen[nn(s1, mu)][mu + 3] = 0;
            }
        }
    }

    // Cluster identification
    int label[N];
    int size[N];
    int ClusterTotal;
    ClusterTotal = FindClusters(label, frozen, size);

    // Flip spins in each cluster with a probability
    for (int i = 1; i <= ClusterTotal; i++) {
        if (((double)rand() / RAND_MAX) < exp(-2.0 * beta * size[i - 1])) {
            for (int j = 0; j < N; j++) {
                if (label[j] == i) {
                    spin[j] *= -1; // Flip the spin
                }
            }
        }
    }
}
