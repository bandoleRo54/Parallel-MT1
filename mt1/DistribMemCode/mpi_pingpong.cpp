#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // This program is designed to run with exactly 2 processes.
    if (size != 2) {
        if (rank == 0) {
            cerr << "Error: This program requires exactly 2 MPI processes." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    
    const int tag = 0;
    int msg;
    
    if (rank == 0) {
        // ---------------------------
        // Round 1: Sender-Initiated RTT
        // ---------------------------
        // Seed the random number generator and generate a random number.
        srand(static_cast<unsigned int>(time(0)));
        msg = rand();
        cout << "Rank 0 (Sender): Generated random number " << msg << endl;
        
        // Start timer, send the message to rank 1, and wait for the reply.
        double start_time = MPI_Wtime();
        MPI_Send(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double sender_rtt = MPI_Wtime() - start_time;
        cout << "Rank 0 (Sender): Received incremented number " << msg 
             << " in " << sender_rtt << " seconds (RTT)." << endl;
        
        // ---------------------------
        // Round 2: Echo for Receiver's RTT Measurement
        // ---------------------------
        // Now act as an echo: receive the message from rank 1 and immediately send it back.
        MPI_Recv(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        
    } else if (rank == 1) {
        // ---------------------------
        // Round 1: Receiver Processes Message
        // ---------------------------
        MPI_Recv(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Rank 1 (Receiver): Received number " << msg << endl;
        
        // Increment the message.
        msg += 1;
        cout << "Rank 1 (Receiver): Incremented number to " << msg << endl;
        
        // Send the incremented message back to rank 0.
        MPI_Send(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        
        // ---------------------------
        // Round 2: Receiver-Initiated RTT
        // ---------------------------
        // Start timer and send the (incremented) message to rank 0.
        double start_time = MPI_Wtime();
        MPI_Send(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        
        // Wait to receive the echo from rank 0.
        MPI_Recv(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double receiver_rtt = MPI_Wtime() - start_time;
        cout << "Rank 1 (Receiver): Message echoed back in " 
             << receiver_rtt << " seconds (RTT)." << endl;
    }
    
    MPI_Finalize();
    return 0;
}
