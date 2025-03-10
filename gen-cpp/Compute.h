/**
 * Autogenerated by Thrift Compiler (0.19.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Compute_H
#define Compute_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "compute_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class ComputeIf {
 public:
  virtual ~ComputeIf() {}
  virtual bool check_availability() = 0;
  virtual void train_model( ::weights& _return, const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep) = 0;
};

class ComputeIfFactory {
 public:
  typedef ComputeIf Handler;

  virtual ~ComputeIfFactory() {}

  virtual ComputeIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ComputeIf* /* handler */) = 0;
  };

class ComputeIfSingletonFactory : virtual public ComputeIfFactory {
 public:
  ComputeIfSingletonFactory(const ::std::shared_ptr<ComputeIf>& iface) : iface_(iface) {}
  virtual ~ComputeIfSingletonFactory() {}

  virtual ComputeIf* getHandler(const ::apache::thrift::TConnectionInfo&) override {
    return iface_.get();
  }
  virtual void releaseHandler(ComputeIf* /* handler */) override {}

 protected:
  ::std::shared_ptr<ComputeIf> iface_;
};

class ComputeNull : virtual public ComputeIf {
 public:
  virtual ~ComputeNull() {}
  bool check_availability() override {
    bool _return = false;
    return _return;
  }
  void train_model( ::weights& /* _return */, const  ::weights& /* coordWeights */, const std::string& /* train_fname */, const double /* eta */, const int32_t /* epochs */, const bool /* sleep */) override {
    return;
  }
};


class Compute_check_availability_args {
 public:

  Compute_check_availability_args(const Compute_check_availability_args&) noexcept;
  Compute_check_availability_args& operator=(const Compute_check_availability_args&) noexcept;
  Compute_check_availability_args() noexcept {
  }

  virtual ~Compute_check_availability_args() noexcept;

  bool operator == (const Compute_check_availability_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Compute_check_availability_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Compute_check_availability_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Compute_check_availability_pargs {
 public:


  virtual ~Compute_check_availability_pargs() noexcept;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Compute_check_availability_result__isset {
  _Compute_check_availability_result__isset() : success(false) {}
  bool success :1;
} _Compute_check_availability_result__isset;

class Compute_check_availability_result {
 public:

  Compute_check_availability_result(const Compute_check_availability_result&) noexcept;
  Compute_check_availability_result& operator=(const Compute_check_availability_result&) noexcept;
  Compute_check_availability_result() noexcept
                                    : success(0) {
  }

  virtual ~Compute_check_availability_result() noexcept;
  bool success;

  _Compute_check_availability_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Compute_check_availability_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Compute_check_availability_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Compute_check_availability_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Compute_check_availability_presult__isset {
  _Compute_check_availability_presult__isset() : success(false) {}
  bool success :1;
} _Compute_check_availability_presult__isset;

class Compute_check_availability_presult {
 public:


  virtual ~Compute_check_availability_presult() noexcept;
  bool* success;

  _Compute_check_availability_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Compute_train_model_args__isset {
  _Compute_train_model_args__isset() : coordWeights(false), train_fname(false), eta(false), epochs(false), sleep(false) {}
  bool coordWeights :1;
  bool train_fname :1;
  bool eta :1;
  bool epochs :1;
  bool sleep :1;
} _Compute_train_model_args__isset;

class Compute_train_model_args {
 public:

  Compute_train_model_args(const Compute_train_model_args&);
  Compute_train_model_args& operator=(const Compute_train_model_args&);
  Compute_train_model_args() noexcept
                           : train_fname(),
                             eta(0),
                             epochs(0),
                             sleep(0) {
  }

  virtual ~Compute_train_model_args() noexcept;
   ::weights coordWeights;
  std::string train_fname;
  double eta;
  int32_t epochs;
  bool sleep;

  _Compute_train_model_args__isset __isset;

  void __set_coordWeights(const  ::weights& val);

  void __set_train_fname(const std::string& val);

  void __set_eta(const double val);

  void __set_epochs(const int32_t val);

  void __set_sleep(const bool val);

  bool operator == (const Compute_train_model_args & rhs) const
  {
    if (!(coordWeights == rhs.coordWeights))
      return false;
    if (!(train_fname == rhs.train_fname))
      return false;
    if (!(eta == rhs.eta))
      return false;
    if (!(epochs == rhs.epochs))
      return false;
    if (!(sleep == rhs.sleep))
      return false;
    return true;
  }
  bool operator != (const Compute_train_model_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Compute_train_model_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Compute_train_model_pargs {
 public:


  virtual ~Compute_train_model_pargs() noexcept;
  const  ::weights* coordWeights;
  const std::string* train_fname;
  const double* eta;
  const int32_t* epochs;
  const bool* sleep;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Compute_train_model_result__isset {
  _Compute_train_model_result__isset() : success(false) {}
  bool success :1;
} _Compute_train_model_result__isset;

class Compute_train_model_result {
 public:

  Compute_train_model_result(const Compute_train_model_result&);
  Compute_train_model_result& operator=(const Compute_train_model_result&);
  Compute_train_model_result() noexcept {
  }

  virtual ~Compute_train_model_result() noexcept;
   ::weights success;

  _Compute_train_model_result__isset __isset;

  void __set_success(const  ::weights& val);

  bool operator == (const Compute_train_model_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Compute_train_model_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Compute_train_model_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Compute_train_model_presult__isset {
  _Compute_train_model_presult__isset() : success(false) {}
  bool success :1;
} _Compute_train_model_presult__isset;

class Compute_train_model_presult {
 public:


  virtual ~Compute_train_model_presult() noexcept;
   ::weights* success;

  _Compute_train_model_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class ComputeClient : virtual public ComputeIf {
 public:
  ComputeClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  ComputeClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool check_availability() override;
  void send_check_availability();
  bool recv_check_availability();
  void train_model( ::weights& _return, const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep) override;
  void send_train_model(const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep);
  void recv_train_model( ::weights& _return);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ComputeProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<ComputeIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) override;
 private:
  typedef  void (ComputeProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_check_availability(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_train_model(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ComputeProcessor(::std::shared_ptr<ComputeIf> iface) :
    iface_(iface) {
    processMap_["check_availability"] = &ComputeProcessor::process_check_availability;
    processMap_["train_model"] = &ComputeProcessor::process_train_model;
  }

  virtual ~ComputeProcessor() {}
};

class ComputeProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ComputeProcessorFactory(const ::std::shared_ptr< ComputeIfFactory >& handlerFactory) noexcept :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) override;

 protected:
  ::std::shared_ptr< ComputeIfFactory > handlerFactory_;
};

class ComputeMultiface : virtual public ComputeIf {
 public:
  ComputeMultiface(std::vector<std::shared_ptr<ComputeIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ComputeMultiface() {}
 protected:
  std::vector<std::shared_ptr<ComputeIf> > ifaces_;
  ComputeMultiface() {}
  void add(::std::shared_ptr<ComputeIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool check_availability() override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->check_availability();
    }
    return ifaces_[i]->check_availability();
  }

  void train_model( ::weights& _return, const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->train_model(_return, coordWeights, train_fname, eta, epochs, sleep);
    }
    ifaces_[i]->train_model(_return, coordWeights, train_fname, eta, epochs, sleep);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class ComputeConcurrentClient : virtual public ComputeIf {
 public:
  ComputeConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  ComputeConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool check_availability() override;
  int32_t send_check_availability();
  bool recv_check_availability(const int32_t seqid);
  void train_model( ::weights& _return, const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep) override;
  int32_t send_train_model(const  ::weights& coordWeights, const std::string& train_fname, const double eta, const int32_t epochs, const bool sleep);
  void recv_train_model( ::weights& _return, const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif
