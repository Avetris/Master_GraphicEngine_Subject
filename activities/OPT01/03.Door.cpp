#include <string>
#include <vector>

struct Float3 {
  float x, y, z;
};

class Entity;

class World {
public:
  // Get a list of all the characters in the world.
  std::vector<Entity *> const &GetCharacters();
  // Get a list of all the doors in the world.
  std::vector<Entity *> const &GetDoors();
};

class Entity {
public:
    float _timeLeftAnimationFinish;
    // Returns the current animation of the entity
    std::string GetAnimation();
    World &GetWorld();
    // Returns the current 3D position (in meters) of the entity within the world
    Float3 GetPosition();
    // Returns the current velocity of the character (in meters per second)
    Float3 GetVelocity();

    // Reduce the time that last to finish the animation
    void Door::ReduceAnimationTime(float timestep) {
        if (_timeLeftAnimationFinish - timestep < 0) {
            _timeLeftAnimationFinish = 0;
        }
        else {
            _timeLeftAnimationFinish -= timestep;
        }
    }

    // Start playing an animation. Animations stop playing (freezing on their
    // final frame) when complete.
    void StartAnimation(std::string const &anim);
    bool Door::IsAnimationComplete() {
        return _timeLeftAnimationFinish == 0;
    }
    // Get the duration of an animation, in seconds
    float GetAnimationDuration(std::string const &anim);
    // Called every frame with the time elapsed since previous frame, in seconds
    virtual void Update(float timestep) = 0;
};

// Represents an automatic door which should open for characters as they
// approach. The following animations are available:
//
// IDLE_CLOSED, IDLE_OPEN, OPENING, CLOSING
//
class Door : public Entity {
public:
  // Candidate to implement. Must try to ensure door is open whenever a
  // character approaches within 1 meter, and is closed otherwise, without
  // snapping animations.
    virtual void Update(float timestep) override {
        ReduceAnimationTime(timestep);
        if (IsAnimationComplete()) {
            if (GetAnimation() == "IDLE_CLOSED") {
                StartAnimation("CLOSING");
            }
            else if (GetAnimation() == "IDLE_OPEN") {
                StartAnimation("OPENING");
            }
            else {
                Float positionLeft = GetPosition();
                Float positionRight = GetPosition();
                positionRight.x += 1;
                positionRight.z += 1;
                positionLeft.x -= 1;
                positionLeft.z -= 1;
                bool hasToOpen = false;
                for (const auto it = GetWorld().GetCharacters().begin(); it < GetWorld().GetCharacters().end() && !hasToAnimate; it++) {
                    Float characterPosition = *it->GetPosition();
                    characterPosition.x += *it->GetVelocity().x; // To open the door before the character arrives to it.
                    characterPosition.z += *it->GetVelocity().z;
                    if (((positionRight.x >= charPosition.x || positionLeft.x <= charPosition.x) &&
                        (positionRight.z >= charPosition.z || positionLeft.z <= charPosition.z)) {
                        hasToOpen = true;
                    }
                }
                if (hasToOpen && GetAnimation() == "CLOSING") {
                    StartAnimation("IDLE_OPEN");
                }
                else if (!hasToOpen && GetAnimation() == "OPENING") {
                    StartAnimation("IDLE_CLOSE");
                }
            }
        }
  }
};

/*
 IDLE_CLOSED -> Door is going to Close
 IDLE_OPEN -> Door is going to Open
 OPENING -> Door is opening or is opened (if animation has finished).
 CLOSING -> Door is closing or is closed (if animation has finished).
*/
