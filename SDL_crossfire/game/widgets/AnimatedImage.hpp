/*
 * AnimatedImage.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_ANIMATEDIMAGE_HPP_
#define GAME_WIDGETS_ANIMATEDIMAGE_HPP_

#include "manager_utils/drawing/Image.hpp"
#include "game/widgets/MoveAnimation.hpp"
#include "game/widgets/SpriteAnimation.hpp"

class AnimatedImage : public MoveAnimation<SpriteAnimation<Image>> {
};

#endif /* GAME_WIDGETS_ANIMATEDIMAGE_HPP_ */
