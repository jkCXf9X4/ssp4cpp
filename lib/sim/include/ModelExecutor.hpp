#pragma once


namespace ssp4cpp::cosim
{
    
    class ModelExecutor {
        public:
        void setParameters();
        void setInput();
        void invoke();
        void getOutput();
    };
    
}