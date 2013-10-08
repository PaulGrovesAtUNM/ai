##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ai
ConfigurationName      :=Debug
WorkspacePath          := "/home/paul/Projects/ai/ai"
ProjectPath            := "/home/paul/Projects/ai/ai"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Paul
Date                   :=10/07/2013
CodeLitePath           :="/home/paul/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="ai.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lm
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/perceptron$(ObjectSuffix) $(IntermediateDirectory)/neuron$(ObjectSuffix) $(IntermediateDirectory)/simpleNeuron$(ObjectSuffix) $(IntermediateDirectory)/neuralNetwork$(ObjectSuffix) $(IntermediateDirectory)/lmsPerceptron$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.c $(IntermediateDirectory)/main$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/perceptron$(ObjectSuffix): perceptron.c $(IntermediateDirectory)/perceptron$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/perceptron.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/perceptron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/perceptron$(DependSuffix): perceptron.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/perceptron$(ObjectSuffix) -MF$(IntermediateDirectory)/perceptron$(DependSuffix) -MM "perceptron.c"

$(IntermediateDirectory)/perceptron$(PreprocessSuffix): perceptron.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/perceptron$(PreprocessSuffix) "perceptron.c"

$(IntermediateDirectory)/neuron$(ObjectSuffix): neuron.c $(IntermediateDirectory)/neuron$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/neuron.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/neuron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/neuron$(DependSuffix): neuron.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/neuron$(ObjectSuffix) -MF$(IntermediateDirectory)/neuron$(DependSuffix) -MM "neuron.c"

$(IntermediateDirectory)/neuron$(PreprocessSuffix): neuron.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/neuron$(PreprocessSuffix) "neuron.c"

$(IntermediateDirectory)/simpleNeuron$(ObjectSuffix): simpleNeuron.c $(IntermediateDirectory)/simpleNeuron$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/simpleNeuron.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/simpleNeuron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/simpleNeuron$(DependSuffix): simpleNeuron.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/simpleNeuron$(ObjectSuffix) -MF$(IntermediateDirectory)/simpleNeuron$(DependSuffix) -MM "simpleNeuron.c"

$(IntermediateDirectory)/simpleNeuron$(PreprocessSuffix): simpleNeuron.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/simpleNeuron$(PreprocessSuffix) "simpleNeuron.c"

$(IntermediateDirectory)/neuralNetwork$(ObjectSuffix): neuralNetwork.c $(IntermediateDirectory)/neuralNetwork$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/neuralNetwork.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/neuralNetwork$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/neuralNetwork$(DependSuffix): neuralNetwork.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/neuralNetwork$(ObjectSuffix) -MF$(IntermediateDirectory)/neuralNetwork$(DependSuffix) -MM "neuralNetwork.c"

$(IntermediateDirectory)/neuralNetwork$(PreprocessSuffix): neuralNetwork.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/neuralNetwork$(PreprocessSuffix) "neuralNetwork.c"

$(IntermediateDirectory)/lmsPerceptron$(ObjectSuffix): lmsPerceptron.c $(IntermediateDirectory)/lmsPerceptron$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/Projects/ai/ai/lmsPerceptron.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lmsPerceptron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lmsPerceptron$(DependSuffix): lmsPerceptron.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lmsPerceptron$(ObjectSuffix) -MF$(IntermediateDirectory)/lmsPerceptron$(DependSuffix) -MM "lmsPerceptron.c"

$(IntermediateDirectory)/lmsPerceptron$(PreprocessSuffix): lmsPerceptron.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lmsPerceptron$(PreprocessSuffix) "lmsPerceptron.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/perceptron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/perceptron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/perceptron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/neuron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/neuron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/neuron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/simpleNeuron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/simpleNeuron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/simpleNeuron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/neuralNetwork$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/neuralNetwork$(DependSuffix)
	$(RM) $(IntermediateDirectory)/neuralNetwork$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lmsPerceptron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lmsPerceptron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lmsPerceptron$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/ai"


