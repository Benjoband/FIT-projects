/**
 * @file ending_message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of EndingMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENDINGMESSAGE_H
#define ENDINGMESSAGE_H

#include "message.h"

namespace communication {
/**
 * @brief Class for EndingMessage, including ending and own serialize and deserialize methods
 * 
 */
class EndingMessage : public Message {
public:
    // enum class for alternative endings
    enum class Ending { IDLE = 0, WIN, LOSE };

    // Constructor
	EndingMessage();

    // Getter
    Ending getEnding() const;

    // Setter
    void setEnding(Ending ending);

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
    Ending _ending = Ending::IDLE;
};

} // namespace communication

#endif // SCOREMESSAGE_H
