##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AIProject
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/pfgrove/.codelite/PerlDev"
ProjectPath            := "/home/pfgrove/Desktop/AI"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Paul
Date                   :=10/04/2013
CodeLitePath           :="/home/pfgrove/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
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
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/Neuron$(ObjectSuffix) $(IntermediateDirectory)/Perceptron$(ObjectSuffix) $(IntermediateDirectory)/InputNeuron$(ObjectSuffix) $(IntermediateDirectory)/NeuralNetwork$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.c $(IntermediateDirectory)/main$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/pfgrove/Desktop/AI/main.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/pfgrove/Desktop/AI/main.c"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/pfgrove/Desktop/AI/main.c"

$(IntermediateDirectory)/Neuron$(ObjectSuffix): Neuron.c $(IntermediateDirectory)/Neuron$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/pfgrove/Desktop/AI/Neuron.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Neuron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Neuron$(DependSuffix): Neuron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Neuron$(ObjectSuffix) -MF$(IntermediateDirectory)/Neuron$(DependSuffix) -MM "/home/pfgrove/Desktop/AI/Neuron.c"

$(IntermediateDirectory)/Neuron$(PreprocessSuffix): Neuron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Neuron$(PreprocessSuffix) "/home/pfgrove/Desktop/AI/Neuron.c"

$(IntermediateDirectory)/Perceptron$(ObjectSuffix): Perceptron.c $(IntermediateDirectory)/Perceptron$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/pfgrove/Desktop/AI/Perceptron.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Perceptron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Perceptron$(DependSuffix): Perceptron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Perceptron$(ObjectSuffix) -MF$(IntermediateDirectory)/Perceptron$(DependSuffix) -MM "/home/pfgrove/Desktop/AI/Perceptron.c"

$(IntermediateDirectory)/Perceptron$(PreprocessSuffix): Perceptron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Perceptron$(PreprocessSuffix) "/home/pfgrove/Desktop/AI/Perceptron.c"

$(IntermediateDirectory)/InputNeuron$(ObjectSuffix): InputNeuron.c $(IntermediateDirectory)/InputNeuron$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/pfgrove/Desktop/AI/InputNeuron.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/InputNeuron$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InputNeuron$(DependSuffix): InputNeuron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/InputNeuron$(ObjectSuffix) -MF$(IntermediateDirectory)/InputNeuron$(DependSuffix) -MM "/home/pfgrove/Desktop/AI/InputNeuron.c"

$(IntermediateDirectory)/InputNeuron$(PreprocessSuffix): InputNeuron.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InputNeuron$(PreprocessSuffix) "/home/pfgrove/Desktop/AI/InputNeuron.c"

$(IntermediateDirectory)/NeuralNetwork$(ObjectSuffix): NeuralNetwork.c $(IntermediateDirectory)/NeuralNetwork$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/pfgrove/Desktop/AI/NeuralNetwork.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/NeuralNetwork$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NeuralNetwork$(DependSuffix): NeuralNetwork.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/NeuralNetwork$(ObjectSuffix) -MF$(IntermediateDirectory)/NeuralNetwork$(DependSuffix) -MM "/home/pfgrove/Desktop/AI/NeuralNetwork.c"

$(IntermediateDirectory)/NeuralNetwork$(PreprocessSuffix): NeuralNetwork.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NeuralNetwork$(PreprocessSuffix) "/home/pfgrove/Desktop/AI/NeuralNetwork.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Neuron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Neuron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Neuron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Perceptron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Perceptron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Perceptron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/InputNeuron$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/InputNeuron$(DependSuffix)
	$(RM) $(IntermediateDirectory)/InputNeuron$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/NeuralNetwork$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/NeuralNetwork$(DependSuffix)
	$(RM) $(IntermediateDirectory)/NeuralNetwork$(PreprocessSuffix)
	$(RM) $(OutputFile)


