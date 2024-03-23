#include "src/class.h"


void launchGame(sf::RenderWindow& window, int character, sf::Font font)
{
    sf::Music music;
    if (!music.openFromFile("Music/game.wav")) {
        // handle error
    }
    music.setLoop(true); // to loop the music
    music.play();

    sf::Texture t;
    t.loadFromFile("imgs/image.png");
    sf::Sprite s(t);
    window.setVerticalSyncEnabled(true);

    Character Guts;
    bool chosenGuts = false;
    Character Shadr;
    bool chosenShadr = false;
    Character firstPlayer;
    Character secondPlayer;

    // Creates a sprite for the 1st player
    sf::Sprite Player;
    if (chosenGuts = true){
        Player.setTexture(IdleGutsSheet[0]);
    }
    else{
        Player.setTexture(IdleShadrSheet[0]);
    }
    Player.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player.setPosition(375, 275);

    //Creates a sprite for the 2nd player
    sf::Sprite Player2;
    if (chosenShadr = true){
        Player2.setTexture(IdleShadrSheet[0]);
    }
    else{
        Player2.setTexture(IdleGutsSheet[0]);
    }
    Player2.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player2.setPosition(200, 200);
    

    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    rectangle.setFillColor(sf::Color::Green); // fill color
    rectangle2.setFillColor(sf::Color::Green); // fill color
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window

    // permet animation player 1
    int currentFrame = 0;
    sf::Clock animationClock;
    bool isRunning = false;
    bool isRunningL = false;
    firstPlayer.isRunning = isRunning;
    firstPlayer.isRunningL = isRunningL;
    bool isJumping = false;
    firstPlayer.isJumping = isJumping;
    bool isCrouch = false;
    firstPlayer.isCrouch = isCrouch;
    bool cannotMove1 = false;
    firstPlayer.cannotMove = cannotMove1;
    bool isAttack1 = false;
    bool isAttack2 = false;
    bool isAttack3 = false;
    firstPlayer.isAttack1 = isAttack1;
    firstPlayer.isAttack2 = isAttack2;
    firstPlayer.isAttack3 = isAttack3;
    bool isDie = false;
    firstPlayer.isDie = isDie;

    // permet animation player 2
    int currentFrame2 = 0;
    sf::Clock animationClock2;
    bool isRunning2 = false;
    bool isRunningL2 = false;
    secondPlayer.isRunning = isRunning2;
    secondPlayer.isRunningL = isRunningL2;
    bool isJumping2 = false;
    secondPlayer.isJumping = isJumping2;
    bool isCrouch2 = false;
    secondPlayer.isCrouch = isCrouch2;
    bool cannotMove2 = false;
    secondPlayer.cannotMove = cannotMove2;
    bool isAttack12 = false;
    bool isAttack22 = false;
    secondPlayer.isAttack1 = isAttack12;
    secondPlayer.isAttack2 = isAttack22;
    bool isDie2 = false;
    secondPlayer.isDie = isDie2;

    float gravity = 0.5f; // gravity force (decreased for longer jumps)
    float velocity1; // initial vertical velocity
    firstPlayer.velocity = velocity1;
    float velocity2; // initial vertical velocity
    secondPlayer.velocity = velocity2;
    int jumps1 = 0; // number of jumps since the last ground contact
    firstPlayer.jumps = jumps1;
    int jumps2 = 0; // number of jumps since the last ground contact
    secondPlayer.jumps = jumps2;
    bool wasZPressed = false;
    firstPlayer.wasZPressed = wasZPressed;
    bool wasYPressed = false;
    secondPlayer.wasZPressed = wasYPressed;
    bool lastDirectionLeft = false; // was the space key pressed during the last iteration?
    firstPlayer.lastDirectionLeft = lastDirectionLeft;
    bool lastDirectionLeft2 = false;
    secondPlayer.lastDirectionLeft = lastDirectionLeft2;

    // Player 1 dash
    bool isDashing1 = false;
    firstPlayer.isDashing = isDashing1;
    float dashDirection1 = 0.0f;
    firstPlayer.dashDirection = dashDirection1;
    float dashDistance1 = 0.0f;
    firstPlayer.dashDistance = dashDistance1;
    sf::Clock dashClock1;

    // Player 2 dash
    bool isDashing2 = false;
    secondPlayer.isDashing = isDashing2;
    float dashDirection2 = 0.0f;
    secondPlayer.dashDirection = dashDirection2;
    float dashDistance2 = 0.0f;
    secondPlayer.dashDistance = dashDistance2;
    sf::Clock dashClock2;

    enum GameState {
        PLAYING,
        PAUSED
    };

    GameState gameState = PLAYING;

    sf::Text backToGameText("Back to Game", font);
    backToGameText.setPosition(700, 200);
    backToGameText.setFillColor(sf::Color::Yellow);
    backToGameText.setScale(2, 2);

    sf::Text backToMenuText("Back to Menu", font);
    backToMenuText.setPosition(700, 400);
    backToMenuText.setFillColor(sf::Color::Yellow);
    backToMenuText.setScale(2, 2);

    sf::Text closeGameText("Close Game", font);
    closeGameText.setPosition(700, 600);
    closeGameText.setFillColor(sf::Color::Yellow);
    closeGameText.setScale(2, 2);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (gameState == PLAYING) {
                    gameState = PAUSED;
                } else if (gameState == PAUSED) {
                    gameState = PLAYING;
                }
            }

            if (gameState == PAUSED && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (backToGameText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    gameState = PLAYING;
                }
                if (backToMenuText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
                if (closeGameText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            gameState = PAUSED;
        }

        window.clear(sf::Color::Black);

        if (gameState == PLAYING) {

            // *** PLAYER 1 ATTACKS ***

            // attack1 player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                firstPlayer.isAttack1 = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % ATTACKLGutsSheet.size();
                        Player.setTexture(ATTACKLGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % ATTACKGutsSheet.size();
                        Player.setTexture(ATTACKGutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isAttack1 = false;
            }

            // attack2 player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                firstPlayer.isAttack2 = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % ATTACK2LGutsSheet.size();
                        Player.setTexture(ATTACK2LGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % ATTACK2GutsSheet.size();
                        Player.setTexture(ATTACK2GutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isAttack2 = false;
            }

            
            // attack3 player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                firstPlayer.isAttack3 = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % ATTACK3LGutsSheet.size();
                        Player.setTexture(ATTACK3LGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % ATTACK3GutsSheet.size();
                        Player.setTexture(ATTACK3GutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isAttack3 = false;
            }

            // *** PLAYER 2 ATTACKS ***

            // attack1 player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
                secondPlayer.isAttack1 = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft2) {
                        currentFrame2 = (currentFrame2 + 1) % ATTACKLShadrSheet.size();
                        Player2.setTexture(ATTACKLShadrSheet[currentFrame2]);
                    } else {
                        currentFrame2 = (currentFrame2 + 1) % ATTACKShadrSheet.size();
                        Player2.setTexture(ATTACKShadrSheet[currentFrame2]);
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isAttack1 = false;
            }

            // attack2 player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                secondPlayer.isAttack2 = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft2) {
                        currentFrame2 = (currentFrame2 + 1) % ATTACK2LShadrSheet.size();
                        Player2.setTexture(ATTACK2LShadrSheet[currentFrame2]);
                    } else {
                        currentFrame2 = (currentFrame2 + 1) % ATTACK2ShadrSheet.size();
                        Player2.setTexture(ATTACK2ShadrSheet[currentFrame2]);
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isAttack2 = false;
            }

            // attack3 player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                secondPlayer.isAttack3 = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % ATTACK2LShadrSheet.size(); // 3 IS NOT DONE YET
                        Player2.setTexture(ATTACK2LShadrSheet[currentFrame]); // 3 IS NOT DONE YET
                    } else {
                        currentFrame = (currentFrame + 1) % ATTACK2ShadrSheet.size(); // 3 IS NOT DONE YET
                        Player2.setTexture(ATTACK2ShadrSheet[currentFrame]); // 3 IS NOT DONE YET
                    }
                    animationClock.restart();
                }
            } else {
                secondPlayer.isAttack3 = false;
            }
            

            // die player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                firstPlayer.isDie = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % DIEGutsSheet.size();
                    Player.setTexture(DIEGutsSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                firstPlayer.isDie = false;
            }

            // die player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                secondPlayer.isDie = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame2 = (currentFrame2 + 1) % DIEShadrSheet.size();
                    Player2.setTexture(DIEShadrSheet[currentFrame2]);
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isDie = false;
            }

            // crouch player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                firstPlayer.isCrouch = true;
                firstPlayer.cannotMove = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (firstPlayer.lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % CRHLGutsSheet.size();
                        Player.setTexture(CRHLGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % CRHGutsSheet.size();
                        Player.setTexture(CRHGutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isCrouch = false;
                firstPlayer.cannotMove = false;
            }

            // crouch player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                secondPlayer.isCrouch = true;
                secondPlayer.cannotMove = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        currentFrame2 = (currentFrame2 + 1) % CRHLShadrSheet.size();
                        Player2.setTexture(CRHLShadrSheet[currentFrame2]);
                    } else {
                        currentFrame2 = (currentFrame2 + 1) % CRHShadrSheet.size();
                        Player2.setTexture(CRHShadrSheet[currentFrame2]);
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isCrouch = false;
                secondPlayer.cannotMove = false;
            }

            // jump and condition player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                firstPlayer.isJumping = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (firstPlayer.lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % JMPLGutsSheet.size();
                        Player.setTexture(JMPLGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % JMPGutsSheet.size();
                        Player.setTexture(JMPGutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isJumping = false;
            }

            if (!firstPlayer.isJumping) {
                if (firstPlayer.isCrouch){
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    firstPlayer.isRunning = true;
                    firstPlayer.lastDirectionLeft = false;
                    // update the sprite every 0.1 seconds
                    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                        currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                        Player.setTexture(runningCharacterSheet[currentFrame]);
                        animationClock.restart();
                    }
                } else {
                    firstPlayer.isRunning = false;
                }
                if (firstPlayer.isCrouch){
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    firstPlayer.isRunningL = true;
                    firstPlayer.lastDirectionLeft = true;
                    // update the sprite every 0.1 seconds
                    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                        currentFrame = (currentFrame + 1) % runLGutsSheet.size();
                        Player.setTexture(runLGutsSheet[currentFrame]);
                        animationClock.restart();
                    }
                } else {
                    firstPlayer.isRunningL = false;
                }
            }

            if (!firstPlayer.isJumping && !firstPlayer.isRunning && !firstPlayer.isRunningL && !firstPlayer.isCrouch) {
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (firstPlayer.lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % IdleLGutsSheet.size();
                        Player.setTexture(IdleLGutsSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % IdleGutsSheet.size();
                        Player.setTexture(IdleGutsSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            }

            // jump and condition player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                secondPlayer.isJumping = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        currentFrame2 = (currentFrame2 + 1) % JMPLShadrSheet.size();
                        Player2.setTexture(JMPLShadrSheet[currentFrame2]);
                    } else {
                        currentFrame2 = (currentFrame2 + 1) % JMPShadrSheet.size();
                        Player2.setTexture(JMPShadrSheet[currentFrame2]);
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isJumping = false;
            }

            if (!secondPlayer.isJumping) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                    secondPlayer.isRunning = true;
                    secondPlayer.lastDirectionLeft = false;
                    // update the sprite every 0.1 seconds
                    if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                        currentFrame2 = (currentFrame2 + 1) % RunShadrSheet.size();
                        Player2.setTexture(RunShadrSheet[currentFrame2]);
                        animationClock2.restart();
                    }
                } else {
                    secondPlayer.isRunning = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    secondPlayer.isRunningL = true;
                    secondPlayer.lastDirectionLeft = true;
                    // update the sprite every 0.1 seconds
                    if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                        currentFrame2 = (currentFrame2 + 1) % RunLShadrSheet.size();
                        Player2.setTexture(RunLShadrSheet[currentFrame2]);
                        animationClock2.restart();
                    }
                } else {
                    secondPlayer.isRunningL = false;
                }
            }

            if (!secondPlayer.isJumping && !secondPlayer.isRunning && !secondPlayer.isRunningL && !secondPlayer.isCrouch) {
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        currentFrame2 = (currentFrame2 + 1) % IdleLShadrSheet.size();
                        Player2.setTexture(IdleLShadrSheet[currentFrame2]);
                    } else {
                        currentFrame2 = (currentFrame2 + 1) % IdleShadrSheet.size();
                        Player2.setTexture(IdleShadrSheet[currentFrame2]);
                    }
                    animationClock2.restart();
                }
            }
            // apply gravity
            float dy1 = firstPlayer.velocity; // save the current velocity for Player1
            float dy2 = secondPlayer.velocity; // save the current velocity for Player2
            firstPlayer.velocity += gravity;
            secondPlayer.velocity += gravity;
            Player.move(0, firstPlayer.velocity);
            Player2.move(0, secondPlayer.velocity);

            // collision player 1
            if (Player.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
                firstPlayer.velocity = 0.0f;
                firstPlayer.jumps = 0;
                Player.setPosition(Player.getPosition().x, rectangle.getPosition().y - Player.getGlobalBounds().height);   
            }

            if (Player.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
                firstPlayer.velocity = 0.0f;
                firstPlayer.jumps = 0;
                Player.setPosition(Player.getPosition().x, rectangle2.getPosition().y - Player.getGlobalBounds().height);   
            }

            if (Player.getPosition().y + Player.getGlobalBounds().height > window.getSize().y)
            {
                Player.setPosition(Player.getPosition().x, window.getSize().y - Player.getGlobalBounds().height);
                firstPlayer.velocity = 0.0f;
                firstPlayer.jumps = 0;
            }

            // collision player 2
            if (Player2.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
                secondPlayer.velocity = 0.0f;
                secondPlayer.jumps = 0;
                Player2.setPosition(Player2.getPosition().x, rectangle.getPosition().y - Player2.getGlobalBounds().height);   
            }

            if (Player2.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
                secondPlayer.velocity = 0.0f;
                secondPlayer.jumps = 0;
                Player2.setPosition(Player2.getPosition().x, rectangle2.getPosition().y - Player2.getGlobalBounds().height);   
            }

            if (Player2.getPosition().y + Player2.getGlobalBounds().height > window.getSize().y)
            {
                Player2.setPosition(Player2.getPosition().x, window.getSize().y - Player2.getGlobalBounds().height);
                secondPlayer.velocity = 0.0f;
                secondPlayer.jumps = 0;
            }

            // jump player 1
            firstPlayer.isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
            if (firstPlayer.isZPressed && !firstPlayer.wasZPressed && firstPlayer.jumps < 2)
            {
                firstPlayer.velocity = firstPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
                firstPlayer.jumps++;
            }
            firstPlayer.wasZPressed = firstPlayer.isZPressed;

            // jump player 2
            secondPlayer.isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
            if (secondPlayer.isZPressed && !secondPlayer.wasZPressed && secondPlayer.jumps < 2)
            {
                secondPlayer.velocity = secondPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
                secondPlayer.jumps++;
            }
            secondPlayer.wasZPressed = secondPlayer.isZPressed;

            // move the player 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getGlobalBounds().left > 0 && !(firstPlayer.cannotMove))
                Player.move(-5, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x && !(firstPlayer.cannotMove))
                Player.move(5, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
                Player.move(0, 12);

            // move the player 2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && Player2.getGlobalBounds().left > 0 && !(secondPlayer.cannotMove))
                Player2.move(-5, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x && !(secondPlayer.cannotMove))
                Player2.move(5, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && Player2.getGlobalBounds().top + Player2.getGlobalBounds().height < window.getSize().y)
                Player2.move(0, 8);

            // dash the player 1
            sf::Time timeSinceLastDash1 = dashClock1.getElapsedTime();
            if (!firstPlayer.isDashing && timeSinceLastDash1.asSeconds() >= 5.0f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player.getGlobalBounds().left > 0) {
                    firstPlayer.isDashing = true;
                    firstPlayer.dashDirection = -20.0f;
                    dashClock1.restart();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) {
                    firstPlayer.isDashing = true;
                    firstPlayer.dashDirection = 20.0f;
                    dashClock1.restart();
                }
            }

            if (firstPlayer.isDashing) {
                if (firstPlayer.dashDistance < 250.0f) {
                    if ((firstPlayer.dashDirection < 0 && Player.getGlobalBounds().left > 0) || 
                        (firstPlayer.dashDirection > 0 && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)) {
                        Player.move(firstPlayer.dashDirection, 0);
                        firstPlayer.dashDistance += std::abs(firstPlayer.dashDirection);
                    } else {
                        firstPlayer.isDashing = false;
                        firstPlayer.dashDistance = 0.0f;
                    }
                } else {
                    firstPlayer.isDashing = false;
                    firstPlayer.dashDistance = 0.0f;
                }
            }

            // dash the player 2
            sf::Time timeSinceLastDash2 = dashClock2.getElapsedTime();
            if (!secondPlayer.isDashing && timeSinceLastDash2.asSeconds() >= 5.0f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && Player2.getGlobalBounds().left > 0) {
                    secondPlayer.isDashing = true;
                    secondPlayer.dashDirection = 20.0f;
                    dashClock2.restart();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) {
                    secondPlayer.isDashing = true;
                    secondPlayer.dashDirection = -20.0f;
                    dashClock2.restart();
                }
            }

            if (secondPlayer.isDashing) {
                if (secondPlayer.dashDistance < 400.0f) {
                    if ((secondPlayer.dashDirection < 0 && Player2.getGlobalBounds().left > 0) || 
                        (secondPlayer.dashDirection > 0 && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x)) {
                        Player2.move(secondPlayer.dashDirection, 0);
                        secondPlayer.dashDistance += std::abs(secondPlayer.dashDirection);
                    } else {
                        secondPlayer.isDashing = false;
                        secondPlayer.dashDistance = 0.0f;
                    }
                } else {
                    secondPlayer.isDashing = false;
                    secondPlayer.dashDistance = 0.0f;
                }
            }

        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(Player);
        window.draw(Player2);
        window.draw(rectangle);
        window.draw(rectangle2);

        } else if (gameState == PAUSED) {
        window.clear(sf::Color::Black);
        window.draw(backToGameText);
        window.draw(backToMenuText);
        window.draw(closeGameText);
    } 

        window.display();
    }
}
