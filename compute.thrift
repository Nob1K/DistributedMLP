include "data.thrift"

service Compute {
    bool check_availability(),
    data.weights train_model(1: data.weights coordWeights, 2: string train_fname, 3: double eta, 4: i32 epochs, 5: bool sleep)
    
}