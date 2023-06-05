
/**
 * @brief send a request without expecting an answer (message)
 * 
 * @param request request to be converted to json and sent to the network
 * @param pt_NetworkHandler Pointer to network handler to be used for the transmission
 */
template<>
void sendRequest<void>(RequestType request, INetworkHandler* pt_NetworkHandler) {
  //void-specific implementation
}