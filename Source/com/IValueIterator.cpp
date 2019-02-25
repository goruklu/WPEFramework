#include "IUnknown.h"
#include "Communicator.h"
#include "IValueIterator.h"

namespace WPEFramework {
namespace ProxyStub {

    // -------------------------------------------------------------------------------------------
    // STUB
    // -------------------------------------------------------------------------------------------

	ProxyStub::MethodHandler ValueIteratorStubMethods[] = {
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

                        uint32_t result = 0;

			// virtual bool Next(string& text) = 0;
			RPC::Data::Frame::Writer response(message->Response().Writer());

			bool valid = message->Parameters().Implementation<RPC::IValueIterator>()->Next(result);

                        response.Boolean(valid);

                        if (valid == true) {
                            response.Number(result);
                        }
		},
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

                        uint32_t result = 0;

			// virtual bool Previous() = 0;
			RPC::Data::Frame::Writer response(message->Response().Writer());

			bool valid = message->Parameters().Implementation<RPC::IValueIterator>()->Previous(result);

                        response.Boolean(valid);

                        if (valid == true) {
                            response.Number(result);
                        }
		},
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

			// virtual void Reset(const uint32_t position) 
			RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

			uint32_t position(parameters.Number<uint32_t>());

			message->Parameters().Implementation<RPC::IValueIterator>()->Reset(position);
		},
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

			// virtual bool IsValid() const = 0;
			RPC::Data::Frame::Writer response(message->Response().Writer());

			response.Boolean(message->Parameters().Implementation<RPC::IValueIterator>()->IsValid());
		},
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

			// virtual uint32_t Count() const = 0;
			RPC::Data::Frame::Writer response(message->Response().Writer());

			response.Number<uint32_t>(message->Parameters().Implementation<RPC::IValueIterator>()->Count());
		},
		[](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {

        		// virtual string Current() const = 0;
			RPC::Data::Frame::Writer response(message->Response().Writer());

			response.Number(message->Parameters().Implementation<RPC::IValueIterator>()->Current());
		},
		nullptr
	};

	typedef ProxyStub::StubType<RPC::IValueIterator, ValueIteratorStubMethods, ProxyStub::UnknownStub> ValueIteratorStub;

    // -------------------------------------------------------------------------------------------
    // PROXY
    // -------------------------------------------------------------------------------------------
	class ValueIteratorProxy : public UnknownProxyType<RPC::IValueIterator> {
	public:
		ValueIteratorProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
			: BaseClass(channel, implementation, otherSideInformed)
		{
			TRACE_L1("Constructed ValueIteratorProxy: %p", this);
		}
		virtual ~ValueIteratorProxy()
		{
			TRACE_L1("Destructed ValueIteratorProxy: %p", this);
		}

	public:
	        virtual bool Next(uint32_t& result) override {
			IPCMessage newMessage(BaseClass::Message(0));

			Invoke(newMessage);

                        RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

			bool valid = reader.Boolean();

                        if (valid == true) {
                           result = reader.Number<uint32_t>();
                        }

			return (valid);
		}
        	virtual bool Previous(uint32_t& result) override {
			IPCMessage newMessage(BaseClass::Message(1));

			Invoke(newMessage);

                        RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

			bool valid = reader.Boolean();

                        if (valid == true) {
                           result = reader.Number<uint32_t>();
                        }
	
			return (valid);
		}
        	virtual void Reset(const uint32_t position) override {
			IPCMessage newMessage(BaseClass::Message(2));
			RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
			writer.Number(position);

			Invoke(newMessage);
		}
        	virtual bool IsValid() const override {
			IPCMessage newMessage(BaseClass::Message(3));

			Invoke(newMessage);

			return (newMessage->Response().Reader().Boolean());
		}
        	virtual uint32_t Count() const override {
			IPCMessage newMessage(BaseClass::Message(4));

			Invoke(newMessage);

			return (newMessage->Response().Reader().Number<uint32_t>());
		}
        	virtual uint32_t Current() const override {
			IPCMessage newMessage(BaseClass::Message(5));

			Invoke(newMessage);

			return (newMessage->Response().Reader().Number<uint32_t>());
		}
	};

    // -------------------------------------------------------------------------------------------
    // Registration
    // -------------------------------------------------------------------------------------------

namespace
{

    class RPCInstantiation {
    public:
        RPCInstantiation()
        {
		RPC::Administrator::Instance().Announce<RPC::IValueIterator, ValueIteratorProxy, ValueIteratorStub>();
	}
        ~RPCInstantiation()
        {
        }

    } RPCRegistration;

}

}
}
