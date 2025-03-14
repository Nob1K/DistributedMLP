/**
 * Autogenerated by Thrift Compiler (0.19.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef coordinator_H
#define coordinator_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "coordinator_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class coordinatorIf {
 public:
  virtual ~coordinatorIf() {}
  virtual double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) = 0;
};

class coordinatorIfFactory {
 public:
  typedef coordinatorIf Handler;

  virtual ~coordinatorIfFactory() {}

  virtual coordinatorIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(coordinatorIf* /* handler */) = 0;
  };

class coordinatorIfSingletonFactory : virtual public coordinatorIfFactory {
 public:
  coordinatorIfSingletonFactory(const ::std::shared_ptr<coordinatorIf>& iface) : iface_(iface) {}
  virtual ~coordinatorIfSingletonFactory() {}

  virtual coordinatorIf* getHandler(const ::apache::thrift::TConnectionInfo&) override {
    return iface_.get();
  }
  virtual void releaseHandler(coordinatorIf* /* handler */) override {}

 protected:
  ::std::shared_ptr<coordinatorIf> iface_;
};

class coordinatorNull : virtual public coordinatorIf {
 public:
  virtual ~coordinatorNull() {}
  double train(const std::string& /* dir */, const int32_t /* rounds */, const int32_t /* epochs */, const int32_t /* h */, const int32_t /* k */, const double /* eta */) override {
    double _return = 0.0;
    return _return;
  }
};

typedef struct _coordinator_train_args__isset {
  _coordinator_train_args__isset() : dir(false), rounds(false), epochs(false), h(false), k(false), eta(false) {}
  bool dir :1;
  bool rounds :1;
  bool epochs :1;
  bool h :1;
  bool k :1;
  bool eta :1;
} _coordinator_train_args__isset;

class coordinator_train_args {
 public:

  coordinator_train_args(const coordinator_train_args&);
  coordinator_train_args& operator=(const coordinator_train_args&);
  coordinator_train_args() noexcept
                         : dir(),
                           rounds(0),
                           epochs(0),
                           h(0),
                           k(0),
                           eta(0) {
  }

  virtual ~coordinator_train_args() noexcept;
  std::string dir;
  int32_t rounds;
  int32_t epochs;
  int32_t h;
  int32_t k;
  double eta;

  _coordinator_train_args__isset __isset;

  void __set_dir(const std::string& val);

  void __set_rounds(const int32_t val);

  void __set_epochs(const int32_t val);

  void __set_h(const int32_t val);

  void __set_k(const int32_t val);

  void __set_eta(const double val);

  bool operator == (const coordinator_train_args & rhs) const
  {
    if (!(dir == rhs.dir))
      return false;
    if (!(rounds == rhs.rounds))
      return false;
    if (!(epochs == rhs.epochs))
      return false;
    if (!(h == rhs.h))
      return false;
    if (!(k == rhs.k))
      return false;
    if (!(eta == rhs.eta))
      return false;
    return true;
  }
  bool operator != (const coordinator_train_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const coordinator_train_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class coordinator_train_pargs {
 public:


  virtual ~coordinator_train_pargs() noexcept;
  const std::string* dir;
  const int32_t* rounds;
  const int32_t* epochs;
  const int32_t* h;
  const int32_t* k;
  const double* eta;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _coordinator_train_result__isset {
  _coordinator_train_result__isset() : success(false) {}
  bool success :1;
} _coordinator_train_result__isset;

class coordinator_train_result {
 public:

  coordinator_train_result(const coordinator_train_result&) noexcept;
  coordinator_train_result& operator=(const coordinator_train_result&) noexcept;
  coordinator_train_result() noexcept
                           : success(0) {
  }

  virtual ~coordinator_train_result() noexcept;
  double success;

  _coordinator_train_result__isset __isset;

  void __set_success(const double val);

  bool operator == (const coordinator_train_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const coordinator_train_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const coordinator_train_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _coordinator_train_presult__isset {
  _coordinator_train_presult__isset() : success(false) {}
  bool success :1;
} _coordinator_train_presult__isset;

class coordinator_train_presult {
 public:


  virtual ~coordinator_train_presult() noexcept;
  double* success;

  _coordinator_train_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class coordinatorClient : virtual public coordinatorIf {
 public:
  coordinatorClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  coordinatorClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) override;
  void send_train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta);
  double recv_train();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class coordinatorProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<coordinatorIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) override;
 private:
  typedef  void (coordinatorProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_train(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  coordinatorProcessor(::std::shared_ptr<coordinatorIf> iface) :
    iface_(iface) {
    processMap_["train"] = &coordinatorProcessor::process_train;
  }

  virtual ~coordinatorProcessor() {}
};

class coordinatorProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  coordinatorProcessorFactory(const ::std::shared_ptr< coordinatorIfFactory >& handlerFactory) noexcept :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) override;

 protected:
  ::std::shared_ptr< coordinatorIfFactory > handlerFactory_;
};

class coordinatorMultiface : virtual public coordinatorIf {
 public:
  coordinatorMultiface(std::vector<std::shared_ptr<coordinatorIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~coordinatorMultiface() {}
 protected:
  std::vector<std::shared_ptr<coordinatorIf> > ifaces_;
  coordinatorMultiface() {}
  void add(::std::shared_ptr<coordinatorIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->train(dir, rounds, epochs, h, k, eta);
    }
    return ifaces_[i]->train(dir, rounds, epochs, h, k, eta);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class coordinatorConcurrentClient : virtual public coordinatorIf {
 public:
  coordinatorConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  coordinatorConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
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
  double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) override;
  int32_t send_train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta);
  double recv_train(const int32_t seqid);
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
