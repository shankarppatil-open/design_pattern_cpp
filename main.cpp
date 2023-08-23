#include<iostream>
#include<list>
#include<string>


/*****************************************************************************/
/// <summary>
/// 
/// </summary>
class IObserver
{
public:
  virtual ~IObserver() { };
  virtual void Update(const std::string& messsge_from_subject) = 0;
};

/// <summary>
/// 
/// </summary>
class ISubject
{
public:
  virtual ~ISubject() {};
  virtual void Attach(IObserver* observer) = 0;
  virtual void Detach(IObserver* observer) = 0;
  virtual void Notify() = 0;
};

/*****************************************************************************/
/// <summary>
/// 
/// </summary>
class Subject :public ISubject
{
private:
  std::list<IObserver*> list_observer_;
  std::string message_;

public:
  /// <summary>
  /// 
  /// </summary>
  virtual ~Subject()
  {
    std::cout << "Goodbye, I was the Subject.\n";  
  }

  /// <summary>
  /// 
  /// </summary>
  /// <param name="pObserver"></param>
  void Attach(IObserver* pObserver) override
  {
    list_observer_.push_back(pObserver);
  }

  /// <summary>
  /// 
  /// </summary>
  /// <param name="pObserver"></param>
  void Detach(IObserver* pObserver) override
  {
    list_observer_.remove(pObserver);
  }

  /// <summary>
  /// 
  /// </summary>
  void Notify() override
  {
    std::list<IObserver*>::iterator _iter = list_observer_.begin();
    PrintObserverCount();
    while (_iter != list_observer_.end())
    {
      (*_iter)->Update(message_);
      ++_iter;
    }
  }

  /// <summary>
  /// 
  /// </summary>
  /// <param name="msg"></param>
  void CreateMessage(std::string msg = "Empty")
  {
    this->message_ = msg;
    Notify();
  }

  void PrintObserverCount()
  {
    std::cout << "There are  " << list_observer_.size() << "  observers in the list\n";
  }

  /// <summary>
  /// 
  /// </summary>
  void SomeBusinessLogic()
  {
    this->message_ = "change message";
    Notify();
    this->message_ = "I am about todo some thing";
  }
};

/*****************************************************************************/
  /// <summary>
  /// 
  /// </summary>
  class Observer :public IObserver
  {
  private:
    std::string message_from_subject_;
    Subject subject_;
    static int Static_number_;
    int number_;

  public:
    Observer(Subject &subject):subject_(subject)
    {
      this->subject_.Attach(this);
      std::cout << "Hi , I am the Observer \"" << this->Static_number_ << "\".\n";
      this->number_ = Observer::Static_number_;
    }

    virtual ~Observer()
    {
      std::cout << "Goodbye, I was Observer\""<<this->number_<<"\".\n";
    }

    void Update(const std::string& message_from_subject) override 
    {
      message_from_subject_ = message_from_subject;
      PrintInfo();
    }

    void RemoveMeFromTheList()
    {
      subject_.Detach(this);
      std::cout << "Observer \"" << this->number_ << "\" removed from the list.\n";
    }

    void PrintInfo()
    {
      std::cout << "Observer \"" << this->number_ << "\": a new message is available -->";
    }
    
  };

  int Observer::Static_number_ = 0;

/*****************************************************************************/
  void ClientCode()
  {
    Subject *subject = new Subject;

    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
  }

  int main() {
    ClientCode();
    return 0;
  }