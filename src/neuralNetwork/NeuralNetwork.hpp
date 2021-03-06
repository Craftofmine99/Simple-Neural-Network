#include <random>
#include <vector>

class NeuralNetwork
{
private:
	int numInput, numOutput, numLayers, numGenerations;
	bool constMembers;
	std::vector<int> numEachLayer;
	std::vector<std::vector<std::vector<std::vector<double>>>> members;
	std::vector<double> myInput;

public:
	// These two values are for generating the random values
	std::mt19937 e2;
	std::uniform_real_distribution<double> dist;
	/**
 * Returns the table (three deep double vector) of
 * the member of the index specified. If the index
 * is out of range, then it returns an empty vector.
 * 
 * Parameters:
 * 	index : integer greater than or equal to zero, and
 * 		less than the number of members.
 * 
 * Returns: Three nested vector of doubles which represent
 * 	the member specified by index.
 */
	std::vector<std::vector<std::vector<double>>> getTableOf(int index);

	/**
 * The only constructor.
 * Mandates a constant network structure (that means the
 * same number of inputs, outputs, layers, and inner nodes
 * for each layer)
 * 
 * Parameters:
 * 	input : Number of input nodes
 * 	innerNodes : Integer vector where the size of the vector
 * 		is the number of layers, and the values represent
 * 		the number of nodes in that layer
 * 	output : Number of outputs
 * 	constMembers : whether or not the amount of members should
 * 		stay constant from one generation to the next
 */
	NeuralNetwork(int input, std::vector<int> innerNodes, int output, bool constMembers);

	/**
 * Must be called before using any other methods.
 * Initializes the number of members.
 * Can also be used to completely reset the current members
 * (but be careful, the other members will be lost forever).
 * 
 * Parameters:
 * 	numNetworks : the number of members to initialize.
 * 
 * Returns: null
 */
	void init(int numNetworks);

	/**
 * Erases all current members.
 * 
 * Parameters: null
 * Returns: null
 */
	void clearMembers();

	/**
 * Erases the set input if it has been set.
 * 
 * Parameters: null
 * Returns: null
 */
	void clearInput();

	/**
 * Sets an input vector to be used in finding the output
 * values of members.
 * 
 * Parameters:
 * 	input : double vector. input.size() should equal this->numInput,
 * 		and each value should be between zero and one.
 * 
 * Returns: true if the vector is valid, false otherwise.
 */
	bool setInput(std::vector<double> input);

	/**
 * 
 * Calculates the output of a single member with the input
 * given by setInput(vector<double> input).
 * 
 * Parameters:
 * 	index : index of the member to get the output for.
 * 
 * Returns : vector of doubles representing the output of the
 * 	specified member and input if setInput() had been called
 * 	before successfully, otherwise returns an empty vector.
 */
	std::vector<double> getOutputOfMember(int index);

	/**
 * Calculates the output of a single member with the input given.
 * 
 * Parameters:
 * 	index : index of the member to get the output for.
 * 	input : double vector prepresenting the input values to
 * 		use to calculate the output.
 * 
 * Returns: the output of the calculation as a double vector, or
 * 	an empty vector if the index or input vector are invalid.
 */
	std::vector<double> getOutputOfMember(int index, std::vector<double> input);

	/**
 * Calculates the outputs for all members with the input
 * specified by setInput(vector<double> input).
 * 
 * Parameters: null
 * Returns: a vector of vectors of doubles representing the
 * 	outputs of all the members.
 */
	std::vector<std::vector<double>> getAllOutputs();

	/**
 * Calculates the outputs for all members with the input
 * specified by input.
 * 
 * Parameters:
 * 	input: a vector of doubles containing the input with which
 * 		the outputs of each member will be calculated.
 * 
 * Returns: a vector of vectors of doubles representing the
 * 	outputs of all the members.
 */
	std::vector<std::vector<double>> getAllOutputs(std::vector<double> input);

	/**
 * Discards specified members and then copies the remaining
 * members to be altered slightly. This is the bread and butter
 * of ML. After a lot of "generations" at least one of the
 * members should be good. It is recommended to allow less than
 * half of the members to move to the next generation. The less
 * the better.
 * 
 * Parameters:
 * 	toNext : a vector of boolean values. The size should be the same
 * 		as the current number of members.
 * 
 * Returns: true if it successfully moves on to the next Generation,
 * 	and false if the input is invalid or there are no members.
 */
	bool nextGen(std::vector<bool> toNext);

	/**
 * Returns a representation of all the current members.
 * 
 * Parameters: null
 * Returns: a representation of all the current members.
 */
	std::string toString();

	/**
 * Returns a representation of the specified member if possible.
 * 
 * Parameters:
 * 	index : the index of the member to get the string
 * 		representation.
 * 
 * Returns: a representation of the specified member if possible,
 * 	otherwise returns an empty string.
 */
	std::string memberToString(int index);

	/**
 * Returns: the current number of members.
 */
	int getNumMembers();

	/**
 * Sets whether or not the nextGen() is allowed to change
 * the number of members.
 * 
 * Parameters:
 * 	c : true = constant amount of members ;
 * 		false = variable amount of members
 * 
 * Returns: null
 */
	void setConstantMembers(bool c);
};
