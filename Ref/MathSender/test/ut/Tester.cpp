// ======================================================================
// \title  MathSender.hpp
// \author kana
// \brief  cpp file for MathSender test harness implementation class
// ======================================================================

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      MathSenderGTestBase("Tester", MAX_HISTORY_SIZE),
      component("MathSender")
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    testAddCommand()
    {
        this->testDoMath(MathOp::ADD);
    }

  void Tester ::
    toDo()
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------
  void Tester ::
    testDoMath(MathOp op)
  {

      // Pick values

      const F32 val1 = 2.0;
      const F32 val2 = 3.0;

      // Send the command

      // pick a command sequence number
      const U32 cmdSeq = 10;
      // send DO_MATH command
      this->sendCmd_DO_MATH(0, cmdSeq, val1, op, val2);
      // retrieve the message from the message queue and dispatch the command to the handler
      this->component.doDispatch();

      // Verify command receipt and response

      // verify command response was sent
      ASSERT_CMD_RESPONSE_SIZE(1);
      // verify the command response was correct as expected
      ASSERT_CMD_RESPONSE(0, MathSenderComponentBase::OPCODE_DO_MATH, cmdSeq, Fw::CmdResponse::OK);

      // Verify operation request on mathOpOut

      // verify that one output port was invoked overall
      ASSERT_FROM_PORT_HISTORY_SIZE(1);
      // verify that the math operation port was invoked once
      ASSERT_from_mathOpOut_SIZE(1);
      // verify the arguments of the operation port
      ASSERT_from_mathOpOut(0, val1, op, val2);

      // Verify telemetry

      // verify that 3 channels were written
      ASSERT_TLM_SIZE(3);
      // verify that the desired telemetry values were sent once
      ASSERT_TLM_VAL1_SIZE(1);
      ASSERT_TLM_VAL2_SIZE(1);
      ASSERT_TLM_OP_SIZE(1);
      // verify that the correct telemetry values were sent
      ASSERT_TLM_VAL1(0, val1);
      ASSERT_TLM_VAL2(0, val2);
      ASSERT_TLM_OP(0, op);

      // Verify event reports

      // verify that one event was sent
      ASSERT_EVENTS_SIZE(1);
      // verify the expected event was sent once
      ASSERT_EVENTS_COMMAND_RECV_SIZE(1);
      // verify the correct event arguments were sent
      ASSERT_EVENTS_COMMAND_RECV(0, val1, op, val2);

  }

  void Tester ::
    from_mathOpOut_handler(
        const NATIVE_INT_TYPE portNum,
        F32 val1,
        const Ref::MathOp &op,
        F32 val2
    )
  {
    this->pushFromPortEntry_mathOpOut(val1, op, val2);
  }

  void Tester ::
    testAddCommand()
{
    this->testDoMath(MathOp::ADD);
}

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts()
  {

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // mathResultIn
    this->connect_to_mathResultIn(
        0,
        this->component.get_mathResultIn_InputPort(0)
    );

    // cmdRegOut
    this->component.set_cmdRegOut_OutputPort(
        0,
        this->get_from_cmdRegOut(0)
    );

    // cmdResponseOut
    this->component.set_cmdResponseOut_OutputPort(
        0,
        this->get_from_cmdResponseOut(0)
    );

    // eventOut
    this->component.set_eventOut_OutputPort(
        0,
        this->get_from_eventOut(0)
    );

    // mathOpOut
    this->component.set_mathOpOut_OutputPort(
        0,
        this->get_from_mathOpOut(0)
    );

    // textEventOut
    this->component.set_textEventOut_OutputPort(
        0,
        this->get_from_textEventOut(0)
    );

    // timeGetOut
    this->component.set_timeGetOut_OutputPort(
        0,
        this->get_from_timeGetOut(0)
    );

    // tlmOut
    this->component.set_tlmOut_OutputPort(
        0,
        this->get_from_tlmOut(0)
    );




  }

  void Tester ::
    initComponents()
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }



} // end namespace Ref
