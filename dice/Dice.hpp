#ifndef SRD_DICE_DICE_H
#define SRD_DICE_DICE_H

namespace dice {

class Dice {
public:
	typedef int result_type;
	virtual auto roll() const-> result_type = 0;
};

}

#endif // SRD_DICE_DICE_H 
