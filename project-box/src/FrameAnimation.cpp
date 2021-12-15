#include "FrameAnimation.h"

FrameAnimation::FrameAnimation(sf::Sprite& target, const float duration)
	: duration_(duration), sumFramesDuration_(0), totalProgress_(0), target_(target)
{
}

void FrameAnimation::AddFrame(float relativeDuration, const sf::IntRect& subrect)
{
	frames_.emplace_back(relativeDuration, subrect);
	sumFramesDuration_ += relativeDuration;
}

void FrameAnimation::AddFrame(float relativeDuration, const sf::IntRect& subrect, sf::Vector2f origin)
{
	frames_.emplace_back(relativeDuration, subrect, origin);
	sumFramesDuration_ += relativeDuration;
}

void FrameAnimation::Update(const float elapsed)
{
	totalProgress_ += elapsed;
	float progress = totalProgress_;

	for (auto& frame : frames_)
	{
		const float frameTime =  frame.relativeDuration / sumFramesDuration_ * duration_;
		progress -= frameTime;

		if (progress <= 0.0f || &frame == &frames_.back())
		{
			target_.setTextureRect(frame.subrect);
			break;
		}
	}

	if(totalProgress_ > duration_)
	{
		totalProgress_ -= duration_;
	}
}
