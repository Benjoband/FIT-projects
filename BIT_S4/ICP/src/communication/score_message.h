/**
 * @file score_message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of ScoreMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SCOREMESSAGE_H
#define SCOREMESSAGE_H

#include "message.h"

namespace communication {

class ScoreMessage : public Message {
public:
    // Constructor
	ScoreMessage();

    // Getters
    int getScore() const;
    int getId() const;
    
    // Setters
    void setScore(int score);
    void setId(int id);

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
    int _score{0};
    int _id{0};
};

} // namespace communication

#endif // SCOREMESSAGE_H
