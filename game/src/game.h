#include "class.h"

void endGameMenu(sf::RenderWindow& window, int character, sf::Font font, bool musicOn, int chosenChar1, int chosenChar2, Character firstPlayer, Character secondPlayer, sf::Music& music, sf::Joystick controller1);
void launchGame(sf::RenderWindow& window, int character, sf::Font font, bool musicOn, int chosenChar1, int chosenChar2, Character firstPlayer, Character secondPlayer);

void launchGame(sf::RenderWindow& window, int character, sf::Font font, bool musicOn, int chosenChar1, int chosenChar2, Character firstPlayer, Character secondPlayer)
{
    sf::Clock chronometer;
    sf::Text Chrono ("", font, 75);
    Chrono.setFillColor(sf::Color::Black);
    Chrono.setPosition(930, 55);
    int maxTime = 120; // 2min of game

    sf::Music music;
    if (!music.openFromFile("Music/game.wav")) {
        // handle error
    }
    music.setLoop(true); // to loop the music

    sf::SoundBuffer soundeffect;
    if (!soundeffect.loadFromFile("Music/soundEffects/dash.wav")){
        // handle error
    }
    sf::Sound dash;
    sf::SoundBuffer soundeffect1;
    if (!soundeffect1.loadFromFile("Music/soundEffects/gutsAttack.wav")) {
        // handle error
    }
    sf::Sound attack2GSound;
    attack2GSound.setBuffer(soundeffect1);
    sf::SoundBuffer soundeffect2;
    if (!soundeffect2.loadFromFile("Music/soundEffects/gutsAttack2.wav")) {
        // handle error
    }
    sf::Sound attackGSound;
    attackGSound.setBuffer(soundeffect2);
    sf::SoundBuffer soundeffect3;
    if (!soundeffect3.loadFromFile("Music/soundEffects/ShadrAttack.wav")) {
        // handle error
    }
    sf::Sound attackSSound;
    attackSSound.setBuffer(soundeffect3);
    sf::SoundBuffer soundeffect4;
    if (!soundeffect4.loadFromFile("Music/soundEffects/ShadrAttack2.wav")) {
        // handle error
    }
    sf::Sound attack2SSound;
    attack2SSound.setBuffer(soundeffect4);
    sf::SoundBuffer soundeffect5;
    if (!soundeffect5.loadFromFile("Music/soundEffects/ShadrSpecial.wav")){
        // handle error
    }
    sf::Sound specialSSound;
    sf::SoundBuffer soundeffect6;
    if (!soundeffect6.loadFromFile("Music/soundEffects/ShadrSpacial2.wav")){
        // handle error
    }
    sf::Sound special2SSound;
    sf::SoundBuffer soundeffect7;
    if (!soundeffect7.loadFromFile("Music/soundEffects/ShadrSpacial2-.wav")){
        // handle error
    }
    sf::Sound special2S_Sound;

    sf::Text GameOver ("Game Over", font);
    GameOver.setPosition(750, 75);
    GameOver.setFillColor(sf::Color::Red);
    GameOver.setScale(4, 4);

    // Load the background image
    sf::Texture texture;
    if (!texture.loadFromFile("imgs/bg3.png")) {
        // Handle error
    }
    // Create a sprite from the texture
    sf::Sprite sprite(texture);
    sprite.scale(3.3, 3.2);
    

    Character Guts;
    Character Shadr;

    // Creates a sprite for the 1st player
    sf::Sprite Player;
    //Creates a sprite for the 2nd player
    sf::Sprite Player2;
    firstPlayer.chosenChar = chosenChar1;
    secondPlayer.chosenChar = chosenChar2;
    if (firstPlayer.chosenChar == 1){
        Player.setTexture(IdleGutsSheet[0]);
    }
    else if (firstPlayer.chosenChar == 2){
        Player.setTexture(IdleShadrSheet[0]);
    }
    if (secondPlayer.chosenChar == 1){
        Player2.setTexture(IdleLGutsSheet[0]);
    }
    else if (secondPlayer.chosenChar == 2){
        Player2.setTexture(IdleLShadrSheet[0]);
    }
    Player.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player.setPosition(250, 250);
    Player2.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player2.setPosition(1500, 250);

    sf::Sprite iconPlayer;
    sf::Sprite iconPlayer2;
    sf::Texture icon1Player;
    icon1Player.loadFromFile("Imgs/p1.png");
    sf::Texture icon2Player;
    icon2Player.loadFromFile("Imgs/p2.png");
    iconPlayer.setTexture(icon1Player);
    iconPlayer2.setTexture(icon2Player);
    iconPlayer.setPosition(Player.getPosition().x + 10, Player.getPosition().y - 5);
    iconPlayer.setScale(sf::Vector2f(2.0f, 2.0));
    iconPlayer2.setPosition(Player2.getPosition().x + 10, Player2.getPosition().y - 5);
    iconPlayer2.setScale(sf::Vector2f(2.0f, 2.0));


    sf::Sprite lifeGuts;
    sf::Sprite lifeShadr;
    sf::Texture charlifeGuts;
    charlifeGuts.loadFromFile("Imgs/Guts/icon.png");
    sf::Texture charlifeShadr;
    charlifeShadr.loadFromFile("Imgs/Shadr/icon.png");
    if (firstPlayer.chosenChar == 1){
        lifeGuts.setTexture(charlifeGuts);
        lifeGuts.setPosition(50, 50);
        lifeGuts.setScale(sf::Vector2f(1.0f, 1.0));
    }
    else if (firstPlayer.chosenChar == 2){
        lifeGuts.setTexture(charlifeShadr);
        lifeGuts.setPosition(50, 50);
        lifeGuts.setScale(sf::Vector2f(1.0f, 1.0));
        
    }
    if (secondPlayer.chosenChar == 1){
        lifeShadr.setTexture(charlifeGuts);
        lifeShadr.setPosition(window.getSize().x - 80, 50);
        lifeShadr.setScale(sf::Vector2f(1.0f, 1.0));
    }
    else if (secondPlayer.chosenChar == 2){
        lifeShadr.setTexture(charlifeShadr);
        lifeShadr.setPosition(window.getSize().x - 80, 50);
        lifeShadr.setScale(sf::Vector2f(1.0f, 1.0));
    }

    // Create a health bar for the first player
    sf::RectangleShape healthBar1(sf::Vector2f(800.0f, 20.0f));
    healthBar1.setFillColor(sf::Color::Red);
    healthBar1.setPosition(10, 10); // Top left
    // Create a health bar for the second player
    sf::RectangleShape healthBar2(sf::Vector2f(800.0f, 20.0f));
    healthBar2.setFillColor(sf::Color::Red);
    healthBar2.setPosition(window.getSize().x - 810, 10); // Top right

    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    rectangle.setFillColor(sf::Color::White); // fill color
    rectangle2.setFillColor(sf::Color::White); // fill color
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window

    // cooldowns
    sf::RectangleShape special1cooldown1(sf::Vector2f(150, 10)); 
    sf::RectangleShape special2cooldown1(sf::Vector2f(150, 10)); 
    special1cooldown1.setPosition(490, 50); // position at the bottom right of the health bar 1
    special2cooldown1.setPosition(490, 65); // position at the bottom left of the health bar 2
    sf::RectangleShape special1cooldown2(sf::Vector2f(150, 10)); 
    sf::RectangleShape special2cooldown2(sf::Vector2f(150, 10)); 
    special1cooldown2.setFillColor(sf::Color::Black); 
    special2cooldown2.setFillColor(sf::Color::Magenta); 
    special1cooldown2.setPosition(window.getSize().x - 650, 50); // position at the bottom right of the health bar 1
    special2cooldown2.setPosition(window.getSize().x - 650, 65); // position at the bottom left of the health bar 2
    if (firstPlayer.chosenChar == 1){
        special1cooldown1.setFillColor(sf::Color::Cyan);
        special2cooldown1.setFillColor(sf::Color::Red);
    }
    else if (firstPlayer.chosenChar == 2){
        special1cooldown1.setFillColor(sf::Color::Black); 
        special2cooldown1.setFillColor(sf::Color::Magenta); 
    }
    if (secondPlayer.chosenChar == 1){
        special1cooldown2.setFillColor(sf::Color::Cyan); 
        special2cooldown2.setFillColor(sf::Color::Red); 
    }
    else if (secondPlayer.chosenChar == 2){
        special1cooldown2.setFillColor(sf::Color::Black); 
        special2cooldown2.setFillColor(sf::Color::Magenta); 
    }
   
    // dash cooldowns
    sf::RectangleShape dashCooldown(sf::Vector2f(150, 10)); 
    dashCooldown.setFillColor(sf::Color::White); 
    dashCooldown.setPosition(650, 50); // position at the bottom right of the health bar 1 (650, 50)
    sf::RectangleShape dashCooldown2(sf::Vector2f(150, 10)); 
    dashCooldown2.setFillColor(sf::Color::White); 
    dashCooldown2.setPosition(window.getSize().x - 810, 50); // position at the bottom right of the health bar 2 (..., 50)

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
    bool isProtect1 = false;
    firstPlayer.isProtect = isProtect1;
    bool isAttack1 = false;
    bool isAttack2 = false;
    firstPlayer.isAttack1 = isAttack1;
    firstPlayer.isAttack2 = isAttack2;
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
    bool isProtect2 = false;
    secondPlayer.isProtect = isProtect2;
    bool isAttack12 = false;
    bool isAttack22 = false;
    secondPlayer.isAttack1 = isAttack12;
    secondPlayer.isAttack2 = isAttack22;
    bool isDie2 = false;
    secondPlayer.isDie = isDie2;

    float gravity1 = 0.5f; // gravity force (decreased for longer jumps)
    float gravity2 = 0.4f;
    int HP1 = 200;
    firstPlayer.maxHP = HP1;
    int HP2 = 200;
    secondPlayer.maxHP = HP2;
    firstPlayer.HP = firstPlayer.maxHP;
    secondPlayer.HP = firstPlayer.maxHP;
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
    bool lastDirectionLeft = false; 
    firstPlayer.lastDirectionLeft = lastDirectionLeft;
    bool lastDirectionLeft2 = true;
    secondPlayer.lastDirectionLeft = lastDirectionLeft2;

    bool wasButton0Pressed = false;
    bool wasSPressed = false;
    bool wasButton3Pressed = false;

    bool isSpecial1P1 = false;
    bool isSpecial2P1 = false;
    bool isSpecial1P2 = false;
    bool isSpecial2P2 = false;
    bool isAttack1P1 = false;
    bool isAttack2P1 = false;
    bool isAttack1P2 = false;
    bool isAttack2P2 = false;
    sf::Clock frameClock;
    float frameDuration = 0.1f;

    sf::Clock frameClock2;
    float frameDuration2 = 0.1f;

    // Attack cooldown
    sf:: Clock basicAttack1Clock1;
    sf:: Clock basicAttack2Clock1;
    sf:: Clock special1AttackClock1;
    sf:: Clock special2AttackClock1;
    sf:: Clock basicAttack1Clock2;
    sf:: Clock basicAttack2Clock2;
    sf:: Clock special1AttackClock2;
    sf:: Clock special2AttackClock2;

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

    int backToGamePos = 200;
    sf::Text backToGameText("Back to Game", font);
    backToGameText.setPosition(700, backToGamePos);
    backToGameText.setFillColor(sf::Color::Yellow);
    backToGameText.setScale(2, 2);

    int backToMenuPos = 400;
    sf::Text backToMenuText("Back to Menu", font);
    backToMenuText.setPosition(700, backToMenuPos);
    backToMenuText.setFillColor(sf::Color::Yellow);
    backToMenuText.setScale(2, 2);

    int closeGamePos = 600;
    sf::Text closeGameText("Close Game", font);
    closeGameText.setPosition(700, closeGamePos);
    closeGameText.setFillColor(sf::Color::Yellow);
    closeGameText.setScale(2, 2);

    int choicePos = backToGamePos;

    bool isZPressed = false;
    bool isSPressed = false;

    float special1Cooldown1 = 3.0f;
    float special2Cooldown1 = 3.0f;
    float special1Cooldown2 = 4.0f;
    float special2Cooldown2 = 5.0f;    
    if (firstPlayer.chosenChar == 1){
        firstPlayer.special1Cooldown = special1Cooldown1;
        firstPlayer.special2Cooldown = special2Cooldown1;
    }
    else if (firstPlayer.chosenChar == 2){
        firstPlayer.special1Cooldown = special1Cooldown2;
        firstPlayer.special2Cooldown = special2Cooldown2;
    }
    if (secondPlayer.chosenChar == 1){
        secondPlayer.special1Cooldown = special1Cooldown1;
        secondPlayer.special2Cooldown = special2Cooldown1;
    }
    else if (secondPlayer.chosenChar == 2){
        secondPlayer.special1Cooldown = special1Cooldown2;
        secondPlayer.special2Cooldown = special2Cooldown2;
    }

    // Constants for joystick sensitivity and neutral position threshold
    const float JoystickSensitivity = 7.5f; // Adjust as needed
    const float JoystickNeutralThreshold = 7.5f; // Adjust as needed
    const float JoystickSensitivity2 = 7.5f;
    const float JoystickNeutralThreshold2 = 7.5f;
    // Previous joystick position
    float prevX = 0.0f;
    float prevY = 0.0f;
    float prevX2 = 0.0f;

    sf::Joystick controller1;
    sf::Joystick controller2;

    while (window.isOpen()) {
        float currentX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float currentY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        float currentX2 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            controller1.update();
            controller2.update();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || controller1.isButtonPressed(0, 6)) {
                if (gameState == PLAYING) {
                    gameState = PAUSED;
                } else if (gameState == PAUSED) {
                    gameState = PLAYING;
                }
            }
            if (musicOn == true){
                if (music.getStatus() != music.Playing){
                    music.play();
                }
                else{
                }
            }
            else{
                music.stop();
            }

            // Color Update depending on your choice
            if (choicePos == backToGamePos) {
                backToGameText.setFillColor(sf::Color::Red);
                backToMenuText.setFillColor(sf::Color::White);
                closeGameText.setFillColor(sf::Color::White);
            } else if (choicePos == backToMenuPos) {
                backToGameText.setFillColor(sf::Color::White);
                backToMenuText.setFillColor(sf::Color::Red);
                closeGameText.setFillColor(sf::Color::White);
            } else if (choicePos == closeGamePos) {
                backToGameText.setFillColor(sf::Color::White);
                backToMenuText.setFillColor(sf::Color::White);
                closeGameText.setFillColor(sf::Color::Red);
            }

            if (gameState == PAUSED) {
                if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY > JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && choicePos < closeGamePos) {
                    if (!wasButton0Pressed && !wasZPressed) {
                        choicePos += 200;
                        wasButton0Pressed = true;
                        wasSPressed = true;
                    }
                } else {    
                    wasButton0Pressed = false;
                    wasSPressed = false;
                }
                if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY < -JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && choicePos > backToGamePos) {
                    if (!wasButton3Pressed && !wasZPressed) {
                       choicePos -= 200;
                       wasButton3Pressed = true;
                       wasZPressed = true;
                    }
                } else {
                    wasButton3Pressed = false;
                    wasZPressed = false;
                }
                if (controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (choicePos == backToGamePos) {
                        gameState = PLAYING;
                    } else if (choicePos == backToMenuPos) {
                        // Go back to the menu and will end all the programs at the end
                        music.stop();
                        system("Pixel-Showdown.exe");
                        system("taskkill /F /IM Pixel-Showdown.exe");
                        
                        return;
                    } else if (choicePos == closeGamePos) {
                        window.close();
                    }
                }
            }
        }

        if (controller1.isButtonPressed(0, 6)) {
            gameState = PAUSED;
        }

        window.clear(sf::Color::Black);

        if (gameState == PLAYING) {

            // *** PLAYER 1 ATTACKS ***

            // attack1 player 1
            if ((controller1.isButtonPressed(0, 2) || sf::Keyboard::isKeyPressed(sf::Keyboard::F)) && !firstPlayer.isProtect && basicAttack1Clock1.getElapsedTime().asSeconds() > 0.5f && !firstPlayer.isAttack1) {
                    currentFrame = 0;
                    firstPlayer.isAttack1 = true;
                    firstPlayer.attackDamage = 0.7;
                    isAttack1P1 = true;
                    frameClock.restart();
                }

            if (isAttack1P1) {
                // update the sprite every 0.1 seconds
                if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
                    frameClock.restart();

                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            attackGSound.play();
                            currentFrame = (currentFrame + 1) % ATTACKLGutsSheet.size();
                            Player.setTexture(ATTACKLGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            attackSSound.play();
                            currentFrame = (currentFrame + 1) % ATTACKLShadrSheet.size();
                            Player.setTexture(ATTACKLShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            attackGSound.play();
                            currentFrame = (currentFrame + 1) % ATTACKGutsSheet.size();
                            Player.setTexture(ATTACKGutsSheet[currentFrame]);
                        }
                        else if(firstPlayer.chosenChar == 2){
                            attackSSound.play();
                            currentFrame = (currentFrame + 1) % ATTACKShadrSheet.size();
                            Player.setTexture(ATTACKShadrSheet[currentFrame]);
                        }
                    }
                    animationClock.restart();
                    if (currentFrame == 0 ) {
                        basicAttack1Clock1.restart();
                        firstPlayer.isAttack1 = false;
                        isAttack1P1 = false;
                    }
                }
            } else {
                firstPlayer.isAttack1 = false;
            }

            // attack2 player 1
            if ((controller1.isButtonPressed(0, 3) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)) && !firstPlayer.isProtect && basicAttack2Clock1.getElapsedTime().asSeconds() > 0.5f && !firstPlayer.isAttack2) {
                    currentFrame = 0;
                    firstPlayer.isAttack2 = true;
                    firstPlayer.attackDamage = 0.7;
                    isAttack2P1 = true;
                    frameClock.restart();
                }

            if (isAttack2P1) {
                // update the sprite every 0.1 seconds
                if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
                    frameClock.restart();

                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            attack2GSound.play();
                            currentFrame = (currentFrame + 1) % ATTACK2LGutsSheet.size();
                            Player.setTexture(ATTACK2LGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            attack2SSound.play();
                            currentFrame = (currentFrame + 1) % ATTACK2LShadrSheet.size();
                            Player.setTexture(ATTACK2LShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            attack2GSound.play();
                            currentFrame = (currentFrame + 1) % ATTACK2GutsSheet.size();
                            Player.setTexture(ATTACK2GutsSheet[currentFrame]);
                        }
                        else if(firstPlayer.chosenChar == 2){
                            attack2SSound.play();
                            currentFrame = (currentFrame + 1) % ATTACK2ShadrSheet.size();
                            Player.setTexture(ATTACK2ShadrSheet[currentFrame]);
                        }
                    }
                    if (currentFrame == 0 ) {
                        basicAttack2Clock1.restart();
                        firstPlayer.isAttack2 = false;
                        isAttack2P1 = false;
                    }
                }
            } else {
                firstPlayer.isAttack2 = false;
            }

            // special1 player 1
            if ((controller1.isButtonPressed(0, 4) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)) && !firstPlayer.isProtect && special1AttackClock1.getElapsedTime().asSeconds() > firstPlayer.special1Cooldown && !firstPlayer.isSpecial1) {
                currentFrame = 0;
                firstPlayer.isSpecial1 = true;
                if (firstPlayer.chosenChar == 1){
                    firstPlayer.attackDamage = 1;
                }
                else if (firstPlayer.chosenChar == 2){
                    firstPlayer.attackDamage = 0.7;
                }
                isSpecial1P1 = true;
                frameClock.restart();
            }

            if (isSpecial1P1) {
                // update the sprite every frameDuration seconds                
                if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
                    frameClock.restart();
                    
                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % SPECIALLGutsSheet.size();
                            Player.setTexture(SPECIALLGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            specialSSound.play();
                            currentFrame = (currentFrame + 1) % SPECIALLShadrSheet.size();
                            Player.setTexture(SPECIALLShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % SPECIALGutsSheet.size();
                            Player.setTexture(SPECIALGutsSheet[currentFrame]);
                        }
                        else if(firstPlayer.chosenChar == 2){
                            specialSSound.play();
                            currentFrame = (currentFrame + 1) % SPECIALShadrSheet.size();
                            Player.setTexture(SPECIALShadrSheet[currentFrame]);
                        }
                    }
                    if (currentFrame == 0 ) {
                        special1AttackClock1.restart();
                        firstPlayer.isSpecial1 = false;
                        isSpecial1P1 = false;
                    }
                }
            } else {
                firstPlayer.isSpecial1 = false;
            }

            // special2 player 1
            if ((controller1.isButtonPressed(0, 5) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) && !firstPlayer.isProtect && special2AttackClock1.getElapsedTime().asSeconds() > firstPlayer.special2Cooldown && !firstPlayer.isSpecial2) {
                    currentFrame = 0;
                    firstPlayer.isSpecial2 = true;
                    if (firstPlayer.chosenChar == 1){
                        firstPlayer.attackDamage = 1;
                    }
                    else if (firstPlayer.chosenChar == 2){
                        firstPlayer.attackDamage = 0.7;
                    }
                    isSpecial2P1 = true;
                    frameClock.restart();
                }   

            if (isSpecial2P1) {
                // update the sprite every 0.1 seconds
                if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
                    frameClock.restart();

                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % SPECIAL2LGutsSheet.size();
                            Player.setTexture(SPECIAL2LGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            special2SSound.play();
                            // special2S_Sound.play();
                            currentFrame = (currentFrame + 1) % SPECIAL2LShadrSheet.size();
                            Player.setTexture(SPECIAL2LShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % SPECIAL2GutsSheet.size();
                            Player.setTexture(SPECIAL2GutsSheet[currentFrame]);
                        }
                        else if(firstPlayer.chosenChar == 2){
                            special2SSound.play();
                            // special2S_Sound.play();
                            currentFrame = (currentFrame + 1) % SPECIAL2ShadrSheet.size();
                            Player.setTexture(SPECIAL2ShadrSheet[currentFrame]);
                        }
                    }
                    if (currentFrame == 0 ) {
                        special2AttackClock1.restart();
                        firstPlayer.isSpecial2 = false;
                        isSpecial2P1 = false;
                    }
                }
            } else {
                firstPlayer.isSpecial2 = false;
            }

            // *** PLAYER 2 ATTACKS ***

            // attack1 player 2
            if (controller2.isButtonPressed(1, 2) && basicAttack1Clock2.getElapsedTime().asSeconds() > 0.5f && !secondPlayer.isAttack1) {
                    currentFrame2 = 0;
                    secondPlayer.isAttack1 = true;
                    secondPlayer.attackDamage = 0.7;
                    isAttack1P2 = true;
                    frameClock2.restart();
                }   

            if (secondPlayer.isAttack1) {
                // update the sprite every 0.1 seconds
                if (frameClock2.getElapsedTime().asSeconds() > frameDuration2) {
                    frameClock2.restart();

                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            attackGSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACKLGutsSheet.size();
                            Player2.setTexture(ATTACKLGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            attackSSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACKLShadrSheet.size();
                            Player2.setTexture(ATTACKLShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            attackGSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACKGutsSheet.size();
                            Player2.setTexture(ATTACKGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            attackSSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACKShadrSheet.size();
                            Player2.setTexture(ATTACKShadrSheet[currentFrame2]);
                        }
                    }
                    if (currentFrame2 == 0 ) {
                        basicAttack1Clock2.restart();
                        secondPlayer.isAttack1 = false;
                        isAttack1P2 = false;
                    }
                }
            } else {
                secondPlayer.isAttack1 = false;
            }

            // attack2 player 2
            if (controller2.isButtonPressed(1, 3) && basicAttack2Clock2.getElapsedTime().asSeconds() > 0.5f && !secondPlayer.isAttack2) {
                    currentFrame2 = 0;
                    secondPlayer.isAttack2 = true;
                    secondPlayer.attackDamage = 0.7;
                    isAttack2P2 = true;
                    frameClock2.restart();
                }

            if (isAttack2P2) {
                // update the sprite every 0.1 seconds
                if (frameClock2.getElapsedTime().asSeconds() > frameDuration2) {
                    frameClock2.restart();

                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            attack2GSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACK2LGutsSheet.size();
                            Player2.setTexture(ATTACK2LGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            attack2SSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACK2LShadrSheet.size();
                            Player2.setTexture(ATTACK2LShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            attack2GSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACK2GutsSheet.size();
                            Player2.setTexture(ATTACK2GutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            attack2SSound.play();
                            currentFrame2 = (currentFrame2 + 1) % ATTACK2ShadrSheet.size();
                            Player2.setTexture(ATTACK2ShadrSheet[currentFrame2]);
                        }
                    }
                    if (currentFrame2 == 0 ) {
                        basicAttack2Clock2.restart();
                        secondPlayer.isAttack2 = false;
                        isAttack2P2 = false;
                    }
                }
            } else {
                secondPlayer.isAttack2 = false;
            }

            // special1 player 2
            if (controller2.isButtonPressed(1, 4) && !secondPlayer.isProtect && special1AttackClock2.getElapsedTime().asSeconds() > secondPlayer.special1Cooldown && !secondPlayer.isSpecial1) {
                    currentFrame2 = 0;
                    secondPlayer.isSpecial1 = true;
                    if (secondPlayer.chosenChar == 1){
                        secondPlayer.attackDamage = 1;
                    }
                    else if (secondPlayer.chosenChar == 2){
                        secondPlayer.attackDamage = 0.7;
                    }
                    isSpecial1P2 = true;
                    frameClock2.restart();
                }

            if (isSpecial1P2) {
                // update the sprite every 0.1 seconds
                if (frameClock2.getElapsedTime().asSeconds() > frameDuration2) {
                    frameClock2.restart();

                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % SPECIALLGutsSheet.size();
                            Player2.setTexture(SPECIALLGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            // specialSSound.play();
                            currentFrame2 = (currentFrame2 + 1) % SPECIALLShadrSheet.size();
                            Player2.setTexture(SPECIALLShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % SPECIALGutsSheet.size();
                            Player2.setTexture(SPECIALGutsSheet[currentFrame2]);
                        }
                        else if(secondPlayer.chosenChar == 2){
                            // specialSSound.play();
                            currentFrame2 = (currentFrame2 + 1) % SPECIALShadrSheet.size();
                            Player2.setTexture(SPECIALShadrSheet[currentFrame2]);
                        }
                    }
                    if (currentFrame2 == 0 ) {
                        special1AttackClock2.restart();
                        secondPlayer.isSpecial1 = false;
                        isSpecial1P2 = false;
                    }
                }
            } else {
                secondPlayer.isSpecial1 = false;
            }

            // special2 player 2
            if (controller2.isButtonPressed(1, 5) && !secondPlayer.isProtect && special2AttackClock1.getElapsedTime().asSeconds() > secondPlayer.special2Cooldown && !secondPlayer.isSpecial2) {
                    currentFrame2 = 0;
                    secondPlayer.isSpecial2 = true;
                    if (secondPlayer.chosenChar == 1){
                        secondPlayer.attackDamage = 0.33;
                    }
                    else if (secondPlayer.chosenChar == 2){
                        secondPlayer.attackDamage = 0.7;
                    }
                    isSpecial2P2 = true;
                    frameClock2.restart();
                }

            if (isSpecial2P2) {
                // update the sprite every 0.1 seconds
                if (frameClock2.getElapsedTime().asSeconds() > frameDuration2) {
                    frameClock2.restart();
                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % SPECIAL2LGutsSheet.size();
                            Player2.setTexture(SPECIAL2LGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            // special2SSound.play();
                            // special2S_Sound.play();
                            currentFrame2 = (currentFrame2 + 1) % SPECIAL2LShadrSheet.size();
                            Player2.setTexture(SPECIAL2LShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % SPECIAL2GutsSheet.size();
                            Player2.setTexture(SPECIAL2GutsSheet[currentFrame2]);
                        }
                        else if(secondPlayer.chosenChar == 2){
                            // special2SSound.play();
                            // special2S_Sound.play();
                            currentFrame2 = (currentFrame2 + 1) % SPECIAL2ShadrSheet.size();
                            Player2.setTexture(SPECIAL2ShadrSheet[currentFrame2]);
                        }
                    }
                    if (currentFrame2 == 0 ) {
                        special2AttackClock2.restart();
                        secondPlayer.isSpecial2 = false;
                        isSpecial2P2 = false;
                    }
                }
            } else {
                secondPlayer.isSpecial2 = false;
            }
            
            // die player 1
            if (firstPlayer.HP == 0) {
                firstPlayer.isDie = true;
                // update the sprite every 0.1 seconds
                if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1) {
                            currentFrame = (currentFrame + 1) % DIELGutsSheet.size();
                            Player.setTexture(DIELGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2) {
                            currentFrame = (currentFrame + 1) % DIELShadrSheet.size(); 
                            Player.setTexture(DIELShadrSheet[currentFrame]); 
                        }
                    }
                    else {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % DIEGutsSheet.size();
                            Player.setTexture(DIEGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            currentFrame = (currentFrame + 1) % DIEShadrSheet.size();
                            Player.setTexture(DIEShadrSheet[currentFrame]);
                        }
                    }
                    frameClock.restart();
                }

                if (currentFrame == DIELGutsSheet.size() - 1 || currentFrame == DIELShadrSheet.size() - 1 || currentFrame == DIEGutsSheet.size() - 1 || currentFrame == DIEShadrSheet.size() - 1) {
                    firstPlayer.lives--;
                    music.stop();
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                }
            } else {
                firstPlayer.isDie = false;
            }

            // die player 2
            if (secondPlayer.HP == 0) {
                secondPlayer.isDie = true;
                // update the sprite every 0.1 seconds
                if (frameClock2.getElapsedTime().asSeconds() > frameDuration2) {
                    frameClock2.restart();
                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1) {
                            currentFrame2 = (currentFrame2 + 1) % DIELGutsSheet.size();
                            Player2.setTexture(DIELGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2) {
                            currentFrame2 = (currentFrame2 + 1) % DIELShadrSheet.size();
                            Player2.setTexture(DIELShadrSheet[currentFrame2]); 
                        }
                    }
                    else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % DIEGutsSheet.size();
                            Player2.setTexture(DIEGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % DIEShadrSheet.size();
                            Player2.setTexture(DIEShadrSheet[currentFrame2]);
                        }
                    }
                    if (currentFrame2 == 0) {
                        secondPlayer.lives--;
                        music.stop();
                        sf::sleep(sf::seconds(1));
                        launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                    }
                }
            } else {
                secondPlayer.isDie = false;
            }

            // crouch player 1
            if (controller1.isButtonPressed(0, 8) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2)) {
                firstPlayer.isCrouch = true;
                firstPlayer.isProtect = true;
                if (firstPlayer.chosenChar == 1){
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
                }
                else if (firstPlayer.chosenChar == 2){
                    // update the sprite every 0.1 seconds
                    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                        if (firstPlayer.lastDirectionLeft) {
                            currentFrame = (currentFrame + 1) % CRHLShadrSheet.size();
                            Player.setTexture(CRHLShadrSheet[currentFrame]);
                        } else {
                            currentFrame = (currentFrame + 1) % CRHShadrSheet.size();
                            Player.setTexture(CRHShadrSheet[currentFrame]);
                        }
                        animationClock.restart();
                    }
                }
            } else {
                firstPlayer.isCrouch = false;
                firstPlayer.isProtect = false;
            }

            // crouch player 2
            if (controller2.isButtonPressed(1, 8) && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2)) {
                secondPlayer.isCrouch = true;
                secondPlayer.isProtect = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % CRHLGutsSheet.size();
                            Player2.setTexture(CRHLGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % CRHLShadrSheet.size();
                            Player2.setTexture(CRHLShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % CRHGutsSheet.size();
                            Player2.setTexture(CRHGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % CRHShadrSheet.size();
                            Player2.setTexture(CRHShadrSheet[currentFrame2]);
                        }
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isCrouch = false;
                secondPlayer.isProtect = false;
            }

            // jump and condition player 1
            if ((controller1.isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2)) {
                firstPlayer.isJumping = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % JMPLGutsSheet.size();
                            Player.setTexture(JMPLGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            currentFrame = (currentFrame + 1) % JMPLShadrSheet.size();
                            Player.setTexture(JMPLShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % JMPGutsSheet.size();
                            Player.setTexture(JMPGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            currentFrame = (currentFrame + 1) % JMPShadrSheet.size();
                            Player.setTexture(JMPShadrSheet[currentFrame]);
                        }
                    }
                    animationClock.restart();
                }
            } else {
                firstPlayer.isJumping = false;
            }

            if (!firstPlayer.isJumping && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2)) {
                if (firstPlayer.isCrouch){
                }
                else if (std::abs(currentX - prevX) > JoystickSensitivity || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    if (currentX > JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        firstPlayer.isRunning = true;
                        firstPlayer.lastDirectionLeft = false;
                        // update the sprite every 0.1 seconds
                        if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                            if (firstPlayer.chosenChar == 1){
                                currentFrame = (currentFrame + 1) % runGutsSheet.size();
                                Player.setTexture(runGutsSheet[currentFrame]);
                            }
                            else if (firstPlayer.chosenChar == 2){
                                currentFrame = (currentFrame + 1) % RunShadrSheet.size();
                                Player.setTexture(RunShadrSheet[currentFrame]);
                            }
                            animationClock.restart();
                        }
                    }
                } else {
                    firstPlayer.isRunning = false;
                }
                if (firstPlayer.isCrouch){
                }
                else if (std::abs(currentX - prevX) > JoystickSensitivity || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    if (currentX < -JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                        firstPlayer.isRunningL = true;
                        firstPlayer.lastDirectionLeft = true;
                        // update the sprite every 0.1 seconds
                        if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                            if (firstPlayer.chosenChar == 1){
                                currentFrame = (currentFrame + 1) % runLGutsSheet.size();
                                Player.setTexture(runLGutsSheet[currentFrame]);
                            }
                            else if (firstPlayer.chosenChar == 2){
                                currentFrame = (currentFrame + 1) % RunLShadrSheet.size();
                                Player.setTexture(RunLShadrSheet[currentFrame]);
                            }
                            animationClock.restart();
                        }
                    }
                } else {
                    firstPlayer.isRunningL = false;
                }
            }

            if (!firstPlayer.isJumping && !firstPlayer.isRunning && !firstPlayer.isRunningL && !firstPlayer.isCrouch && !firstPlayer.isAttack1 && !firstPlayer.isAttack2 && !firstPlayer.isSpecial1 && !firstPlayer.isSpecial2 && !firstPlayer.isDie) {
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (firstPlayer.lastDirectionLeft) {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % IdleLGutsSheet.size();
                            Player.setTexture(IdleLGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            currentFrame = (currentFrame + 1) % IdleLShadrSheet.size();
                            Player.setTexture(IdleLShadrSheet[currentFrame]);
                        }
                    } else {
                        if (firstPlayer.chosenChar == 1){
                            currentFrame = (currentFrame + 1) % IdleGutsSheet.size();
                            Player.setTexture(IdleGutsSheet[currentFrame]);
                        }
                        else if (firstPlayer.chosenChar == 2){
                            currentFrame = (currentFrame + 1) % IdleShadrSheet.size();
                            Player.setTexture(IdleShadrSheet[currentFrame]);
                        }
                    }
                    animationClock.restart();
                }
            }

            // jump and condition player 2
            if ((controller2.isButtonPressed(1, 0)) && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2)) {
                secondPlayer.isJumping = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % JMPLGutsSheet.size();
                            Player2.setTexture(JMPLGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % JMPLShadrSheet.size();
                            Player2.setTexture(JMPLShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % JMPGutsSheet.size();
                            Player2.setTexture(JMPGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % JMPShadrSheet.size();
                            Player2.setTexture(JMPShadrSheet[currentFrame2]);
                        }
                    }
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isJumping = false;
            }

            if (!secondPlayer.isJumping && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2)) {
                if (secondPlayer.isCrouch){
                }
                else if (std::abs(currentX2 - prevX2) > JoystickSensitivity2) {
                    if (currentX2 > JoystickNeutralThreshold2) {
                        secondPlayer.isRunning = true;
                        secondPlayer.lastDirectionLeft = false;
                        // update the sprite every 0.1 seconds
                        if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                            if (secondPlayer.chosenChar == 1){
                                currentFrame2 = (currentFrame2 + 1) % runGutsSheet.size();
                                Player2.setTexture(runGutsSheet[currentFrame2]);
                            }
                            else if (secondPlayer.chosenChar == 2){
                                currentFrame2 = (currentFrame2 + 1) % RunShadrSheet.size();
                                Player2.setTexture(RunShadrSheet[currentFrame2]);
                            }
                            animationClock2.restart();
                        }
                    }
                } else {
                    secondPlayer.isRunning = false;
                }
                if (secondPlayer.isCrouch){
                }
                else if (std::abs(currentX2 - prevX2) > JoystickSensitivity2) {
                    if (currentX2 < -JoystickNeutralThreshold2) {
                        secondPlayer.isRunningL = true;
                        secondPlayer.lastDirectionLeft = true;
                        // update the sprite every 0.1 seconds
                        if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                            if (secondPlayer.chosenChar == 1){
                                currentFrame2 = (currentFrame2 + 1) % runLGutsSheet.size();
                                Player2.setTexture(runLGutsSheet[currentFrame2]);
                            }
                            else if (secondPlayer.chosenChar == 2){
                                currentFrame2 = (currentFrame2 + 1) % RunLShadrSheet.size();
                                Player2.setTexture(RunLShadrSheet[currentFrame2]);
                            }
                            animationClock2.restart();
                        }
                    }
                } else {
                    secondPlayer.isRunningL = false;
                }
            }

            if (!secondPlayer.isJumping && !secondPlayer.isRunning && !secondPlayer.isRunningL && !secondPlayer.isCrouch && !secondPlayer.isAttack1 && !secondPlayer.isAttack2 && !secondPlayer.isSpecial1 && !secondPlayer.isSpecial2 && !secondPlayer.isDie) {
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    if (secondPlayer.lastDirectionLeft) {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % IdleLGutsSheet.size();
                            Player2.setTexture(IdleLGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % IdleLShadrSheet.size();
                            Player2.setTexture(IdleLShadrSheet[currentFrame2]);
                        }
                    } else {
                        if (secondPlayer.chosenChar == 1){
                            currentFrame2 = (currentFrame2 + 1) % IdleGutsSheet.size();
                            Player2.setTexture(IdleGutsSheet[currentFrame2]);
                        }
                        else if (secondPlayer.chosenChar == 2){
                            currentFrame2 = (currentFrame2 + 1) % IdleShadrSheet.size();
                            Player2.setTexture(IdleShadrSheet[currentFrame2]);
                        }
                    }
                    animationClock2.restart();
                }
            }
            
            // apply gravity
            float dy1 = firstPlayer.velocity; // save the current velocity for Player1
            float dy2 = secondPlayer.velocity; // save the current velocity for Player2
            if (firstPlayer.chosenChar == 1){
                firstPlayer.velocity += gravity1;
            }
            else if (firstPlayer.chosenChar == 2){
                firstPlayer.velocity += gravity2;
            }
            if (secondPlayer.chosenChar == 1){
                secondPlayer.velocity += gravity1;
            }
            else if (secondPlayer.chosenChar == 2){
                secondPlayer.velocity += gravity2;
            }
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
            firstPlayer.isZPressed = (controller1.isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
            if (firstPlayer.isZPressed && !firstPlayer.wasZPressed && firstPlayer.jumps < 2 && !firstPlayer.isProtect && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2))
            {
                firstPlayer.velocity = firstPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
                firstPlayer.jumps++;
            }
            firstPlayer.wasZPressed = firstPlayer.isZPressed;

            // jump player 2
            secondPlayer.isZPressed = controller1.isButtonPressed(1, 0);
            if (secondPlayer.isZPressed && !secondPlayer.wasZPressed && secondPlayer.jumps < 2 && !secondPlayer.isProtect && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2))
            {
                secondPlayer.velocity = secondPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
                secondPlayer.jumps++;
            }
            secondPlayer.wasZPressed = secondPlayer.isZPressed;

            // move the player 1
            if (firstPlayer.chosenChar == 1){
                // Move player left or right based on joystick position
                if (!(firstPlayer.isProtect) && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2)){
                    if ((currentX < -JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && Player.getGlobalBounds().left > 0)
                        Player.move(-5, 0); // Move left
                    else if ((currentX > JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)
                        Player.move(5, 0); // Move right
                    else if (sf::Joystick::isButtonPressed(0, 8) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
                        Player.move(0, 9);
                    else {
                        // Reset player movement
                        Player.move(0, 0);
                    }
                }
            }
            else if (firstPlayer.chosenChar == 2){
                if (!(firstPlayer.isProtect) && !(firstPlayer.isAttack1 || firstPlayer.isAttack2 || firstPlayer.isSpecial1 || firstPlayer.isSpecial2)){
                    if ((currentX < -JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && Player.getGlobalBounds().left > 0) // Move left
                        Player.move(-7, 0);
                    else if ((currentX > JoystickNeutralThreshold || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) // Move right
                        Player.move(7, 0);
                    else if (sf::Joystick::isButtonPressed(0, 8) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
                        Player.move(0, 5);
                    else{
                        // Rest player movement
                        Player.move(0, 0);
                    }
                }
            }

            // move the player 2
            if (secondPlayer.chosenChar == 1){
                // Move player left or right based on joystick position
                if (!(secondPlayer.isProtect) && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2)){
                    if (currentX2 < -JoystickNeutralThreshold2 && Player2.getGlobalBounds().left > 0)
                        Player2.move(-5, 0); // Move left
                    else if (currentX2 > JoystickNeutralThreshold2 && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x)
                        Player2.move(5, 0); // Move right
                    else if (sf::Joystick::isButtonPressed(0, 8) && Player2.getGlobalBounds().top + Player2.getGlobalBounds().height < window.getSize().y)
                        Player2.move(0, 9);
                    else {
                        // Reset player movement
                        Player2.move(0, 0);
                    }
                }
            }
            else if (secondPlayer.chosenChar == 2){
                if (!(secondPlayer.isProtect) && !(secondPlayer.isAttack1 || secondPlayer.isAttack2 || secondPlayer.isSpecial1 || secondPlayer.isSpecial2)){
                    if (currentX2 < -JoystickNeutralThreshold2 && Player2.getGlobalBounds().left > 0) // Move left
                        Player2.move(-7, 0);
                    else if (currentX2 > JoystickNeutralThreshold2 && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) // Move right
                        Player2.move(7, 0);
                    else if (sf::Joystick::isButtonPressed(0, 8) && Player2.getGlobalBounds().top + Player2.getGlobalBounds().height < window.getSize().y)
                        Player2.move(0, 5);
                    else{
                        // Rest player movement
                        Player2.move(0, 0);
                    }
                }
            }

            // dash the player 1
            sf::Time timeSinceLastDash1 = dashClock1.getElapsedTime();
            if (firstPlayer.chosenChar == 1){
                if (!firstPlayer.isDashing && timeSinceLastDash1.asSeconds() >= firstPlayer.dashCooldown) {
                    if ((controller1.isButtonPressed(0, 1) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) {
                        if (firstPlayer.lastDirectionLeft){
                            firstPlayer.isDashing = true;
                            firstPlayer.dashDirection = -20.0f;
                            dashClock1.restart();
                        }
                        else{
                            firstPlayer.isDashing = true;
                            firstPlayer.dashDirection = 20.0f;
                            dashClock1.restart();
                        }
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
            }
            else if (firstPlayer.chosenChar == 2){
                if (!firstPlayer.isDashing && timeSinceLastDash1.asSeconds() >= 5.0f) {
                    if (controller1.isButtonPressed(0, 1) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) {
                        if (firstPlayer.lastDirectionLeft){
                            firstPlayer.isDashing = true;
                            firstPlayer.dashDirection = -20.0f;
                            dashClock1.restart();
                        }
                        else{
                            firstPlayer.isDashing = true;
                            firstPlayer.dashDirection = 20.0f;
                            dashClock1.restart();
                        }
                    }
                }

                if (firstPlayer.isDashing) {
                    if (firstPlayer.dashDistance < 400.0f) {
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
            }

            // dash the player 2
            sf::Time timeSinceLastDash2 = dashClock2.getElapsedTime();
            if (secondPlayer.chosenChar == 1){
                if (!secondPlayer.isDashing && timeSinceLastDash2.asSeconds() >= secondPlayer.dashCooldown) {
                    if (controller2.isButtonPressed(1, 1) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) {
                        if (secondPlayer.lastDirectionLeft){
                            secondPlayer.isDashing = true;
                            secondPlayer.dashDirection = -20.0f;
                            dashClock2.restart();
                        }
                        else{
                            secondPlayer.isDashing = true;
                            secondPlayer.dashDirection = 20.0f;
                            dashClock2.restart();
                        }
                    }
                }

                if (secondPlayer.isDashing) {
                    if (secondPlayer.dashDistance < 250.0f) {
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
            }
            else if (secondPlayer.chosenChar == 2){
                if (!secondPlayer.isDashing && timeSinceLastDash2.asSeconds() >= 5.0f) {
                    if (controller2.isButtonPressed(1, 1) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) {
                        if (secondPlayer.lastDirectionLeft){
                            secondPlayer.isDashing = true;
                            secondPlayer.dashDirection = -20.0f;
                            dashClock2.restart();
                        }
                        else{
                            secondPlayer.isDashing = true;
                            secondPlayer.dashDirection = 20.0f;
                            dashClock2.restart();
                        }
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
            }


            // ATACKS DAMAGES

            // Check if player 1 is attacking
            if (firstPlayer.isAttack1 && Player.getGlobalBounds().intersects(Player2.getGlobalBounds())) {
                if ((Player.getPosition().x < Player2.getPosition().x && !firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && secondPlayer.lastDirectionLeft)) || (Player.getPosition().x > Player2.getPosition().x && firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && !secondPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    secondPlayer.HP -= firstPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (secondPlayer.HP < 0) {
                    secondPlayer.HP = 0;
                    secondPlayer.isDie = true;
                }
            }
            else if (firstPlayer.isAttack2 && Player.getGlobalBounds().intersects(Player2.getGlobalBounds())){
                if ((Player.getPosition().x < Player2.getPosition().x && !firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && secondPlayer.lastDirectionLeft)) || (Player.getPosition().x > Player2.getPosition().x && firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && !secondPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    secondPlayer.HP -= firstPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (secondPlayer.HP < 0) {
                    secondPlayer.HP = 0;
                    secondPlayer.isDie = true;
                }  
            }
            else if (firstPlayer.isSpecial1 && Player.getGlobalBounds().intersects(Player2.getGlobalBounds())){
                if ((Player.getPosition().x < Player2.getPosition().x && !firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && secondPlayer.lastDirectionLeft)) || (Player.getPosition().x > Player2.getPosition().x && firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && !secondPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    secondPlayer.HP -= firstPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (secondPlayer.HP < 0) {
                    secondPlayer.HP = 0;
                    secondPlayer.isDie = true;
                }  
            }
            else if (firstPlayer.isSpecial2 && Player.getGlobalBounds().intersects(Player2.getGlobalBounds())){
                if ((Player.getPosition().x < Player2.getPosition().x && !firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && secondPlayer.lastDirectionLeft)) || (Player.getPosition().x > Player2.getPosition().x && firstPlayer.lastDirectionLeft && !(secondPlayer.isProtect && !secondPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    secondPlayer.HP -= firstPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (secondPlayer.HP < 0) {
                    secondPlayer.HP = 0;
                    secondPlayer.isDie = true;
                }  
            }

            // Check if player 2 is attacking
            if (secondPlayer.isAttack1 && Player2.getGlobalBounds().intersects(Player.getGlobalBounds())) {
                if ((Player2.getPosition().x < Player.getPosition().x && !secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && firstPlayer.lastDirectionLeft)) || (Player2.getPosition().x > Player.getPosition().x && secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && !firstPlayer.lastDirectionLeft))){
                    // Check if player 2's attack hits player 1
                    // Reduce player 1's health
                    firstPlayer.HP -= secondPlayer.attackDamage;
                }
                // Make sure player 1's health doesn't fall below zero
                if (firstPlayer.HP < 0) {
                    firstPlayer.HP = 0;
                    firstPlayer.isDie = true;
                }                
            }
            else if (secondPlayer.isAttack2 && Player2.getGlobalBounds().intersects(Player.getGlobalBounds())) {
                if ((Player2.getPosition().x < Player.getPosition().x && !secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && firstPlayer.lastDirectionLeft)) || (Player2.getPosition().x > Player.getPosition().x && secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && !firstPlayer.lastDirectionLeft))){
                    // Check if player 2's attack hits player 1
                    // Reduce player 1's health
                    firstPlayer.HP -= secondPlayer.attackDamage;
                }
                // Make sure player 1's health doesn't fall below zero
                if (firstPlayer.HP < 0) {
                    firstPlayer.HP = 0;
                    firstPlayer.isDie = true;
                }                
            }
            else if (secondPlayer.isSpecial1 && Player2.getGlobalBounds().intersects(Player.getGlobalBounds())){
                if ((Player2.getPosition().x < Player.getPosition().x && !secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && firstPlayer.lastDirectionLeft)) || (Player2.getPosition().x > Player.getPosition().x && secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && !firstPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    firstPlayer.HP -= secondPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (firstPlayer.HP < 0) {
                    firstPlayer.HP = 0;
                    firstPlayer.isDie = true;
                }  
            }
            else if (secondPlayer.isSpecial2 && Player2.getGlobalBounds().intersects(Player.getGlobalBounds())){
                if ((Player2.getPosition().x < Player.getPosition().x && !secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && firstPlayer.lastDirectionLeft)) || (Player2.getPosition().x > Player.getPosition().x && secondPlayer.lastDirectionLeft && !(firstPlayer.isProtect && !firstPlayer.lastDirectionLeft))){
                    // Check if player 1's attack hits player 2
                    // Reduce player 2's health
                    firstPlayer.HP -= secondPlayer.attackDamage;
                }
                // Make sure player 2's health doesn't fall below zero
                if (firstPlayer.HP < 0) {
                    firstPlayer.HP = 0;
                    firstPlayer.isDie = true;
                }
            }

            // Update the health bar for the first player
            healthBar1.setSize(sf::Vector2f(800.0f * firstPlayer.HP / firstPlayer.maxHP, 20.0f));

            // Update the health bar for the second player
            healthBar2.setSize(sf::Vector2f(800.0f * secondPlayer.HP / secondPlayer.maxHP, 20.0f));


            // update the visible cooldowns
            if (special1AttackClock1.getElapsedTime().asSeconds() < firstPlayer.special1Cooldown){
                special1cooldown1.setSize(sf::Vector2f(150 * special1AttackClock1.getElapsedTime().asSeconds() / firstPlayer.special1Cooldown, 10.0f));
            }
            if (special2AttackClock1.getElapsedTime().asSeconds() < firstPlayer.special2Cooldown){
                special2cooldown1.setSize(sf::Vector2f(150 * special2AttackClock1.getElapsedTime().asSeconds() / firstPlayer.special2Cooldown, 10.0f));
            }
            if (special1AttackClock2.getElapsedTime().asSeconds() < secondPlayer.special1Cooldown){
                special1cooldown2.setSize(sf::Vector2f(150 * special1AttackClock2.getElapsedTime().asSeconds() / secondPlayer.special1Cooldown, 10.0f));
            }
            if (special2AttackClock2.getElapsedTime().asSeconds() < secondPlayer.special2Cooldown){
                special2cooldown2.setSize(sf::Vector2f(150 * special2AttackClock2.getElapsedTime().asSeconds() / secondPlayer.special2Cooldown, 10.0f));
            }
            if (timeSinceLastDash1.asSeconds() <= firstPlayer.dashCooldown){
                dashCooldown.setSize(sf::Vector2f(150 * timeSinceLastDash1.asSeconds() / firstPlayer.dashCooldown, 10.0f));

            }
            if (timeSinceLastDash2.asSeconds() <= secondPlayer.dashCooldown){
                dashCooldown2.setSize(sf::Vector2f(150 * timeSinceLastDash2.asSeconds() / secondPlayer.dashCooldown, 10.0f));
            }

            if (firstPlayer.lives == 0 || secondPlayer.lives == 0) {
                music.stop();
                std::stringstream Ss;
                Ss << (firstPlayer.lives == 0 ? "2nd Player won" : "1st Player won");
                GameOver.setString(Ss.str());
                window.draw(GameOver);
                window.display();
                sf::sleep(sf::seconds(1));
                endGameMenu(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer, music, controller1);
                return;
            }

            iconPlayer.setTexture(icon1Player);
            if (firstPlayer.chosenChar == 1){
                iconPlayer.setPosition(Player.getPosition().x + 75, Player.getPosition().y - 5);
            }
            else if (firstPlayer.chosenChar == 2){
                iconPlayer.setPosition(Player.getPosition().x + 75, Player.getPosition().y + 65);
            }
            iconPlayer2.setTexture(icon2Player);
            if (secondPlayer.chosenChar == 1){
                iconPlayer2.setPosition(Player2.getPosition().x + 75, Player2.getPosition().y - 5);
            }
            else if (secondPlayer.chosenChar == 2){
                iconPlayer2.setPosition(Player2.getPosition().x + 75, Player2.getPosition().y + 65);
            }



        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(Player);
        window.draw(Player2);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(healthBar1);
        window.draw(healthBar2);
        window.draw(lifeGuts);
        window.draw(lifeShadr);
        window.draw(special1cooldown1);
        window.draw(special1cooldown2);
        window.draw(special2cooldown1);
        window.draw(special2cooldown2);
        window.draw(dashCooldown);
        window.draw(dashCooldown2);
        window.draw(iconPlayer);
        window.draw(iconPlayer2);
                


                if (firstPlayer.lives >= 2){
                    if (firstPlayer.chosenChar == 1){
                        sf::Sprite lifeGuts2;
                        sf::Texture charlifeGuts2;
                        charlifeGuts2.loadFromFile("Imgs/Guts/icon.png");
                        lifeGuts2.setTexture(charlifeGuts2);
                        lifeGuts2.setPosition(100, 50);
                        lifeGuts2.setScale(sf::Vector2f(1.0f, 1.0));
                        window.draw(lifeGuts2);
                        if (firstPlayer.lives == 3){
                            sf::Sprite lifeGuts3;
                            sf::Texture charlifeGuts3;
                            charlifeGuts3.loadFromFile("Imgs/Guts/icon.png");
                            lifeGuts3.setTexture(charlifeGuts3);
                            lifeGuts3.setPosition(150, 50);
                            lifeGuts3.setScale(sf::Vector2f(1.0f, 1.0));
                            window.draw(lifeGuts3);
                        }
                    }
                    else{
                        sf::Sprite lifeShadr2;
                        sf::Texture charlifeShadr2;
                        charlifeShadr2.loadFromFile("Imgs/Shadr/icon.png");
                        lifeShadr2.setTexture(charlifeShadr2);
                        lifeShadr2.setPosition(100, 50);
                        lifeShadr2.setScale(sf::Vector2f(1.0f, 1.0));
                        window.draw(lifeShadr2);
                        if (firstPlayer.lives == 3){
                            sf::Sprite lifeShadr3;
                            sf::Texture charlifeShadr3;
                            charlifeShadr3.loadFromFile("Imgs/Shadr/icon.png");
                            lifeShadr3.setTexture(charlifeShadr3);
                            lifeShadr3.setPosition(150, 50);
                            lifeShadr3.setScale(sf::Vector2f(1.0f, 1.0));
                            window.draw(lifeShadr3);
                        }
                    }
                }
                if (secondPlayer.lives >= 2){
                    if (secondPlayer.chosenChar == 1){
                        sf::Sprite lifeGuts2;
                        sf::Texture charlifeGuts2;
                        charlifeGuts2.loadFromFile("Imgs/Guts/icon.png");
                        lifeGuts2.setTexture(charlifeGuts2);
                        lifeGuts2.setPosition(window.getSize().x - 130, 50);
                        lifeGuts2.setScale(sf::Vector2f(1.0f, 1.0));
                        window.draw(lifeGuts2);
                        if (secondPlayer.lives == 3){
                            sf::Sprite lifeGuts3;
                            sf::Texture charlifeGuts3;
                            charlifeGuts3.loadFromFile("Imgs/Guts/icon.png");
                            lifeGuts3.setTexture(charlifeGuts3);
                            lifeGuts3.setPosition(window.getSize().x - 180, 50);
                            lifeGuts3.setScale(sf::Vector2f(1.0f, 1.0));
                            window.draw(lifeGuts3);
                        }
                    }
                    else{
                        sf::Sprite lifeShadr2;
                        sf::Texture charlifeShadr2;
                        charlifeShadr2.loadFromFile("Imgs/Shadr/icon.png");
                        lifeShadr2.setTexture(charlifeShadr2);
                        lifeShadr2.setPosition(window.getSize().x - 130, 50);
                        lifeShadr2.setScale(sf::Vector2f(1.0f, 1.0));
                        window.draw(lifeShadr2);
                        if (secondPlayer.lives == 3){
                            sf::Sprite lifeShadr3;
                            sf::Texture charlifeShadr3;
                            charlifeShadr3.loadFromFile("Imgs/Shadr/icon.png");
                            lifeShadr3.setTexture(charlifeShadr3);
                            lifeShadr3.setPosition(window.getSize().x - 180, 50);
                            lifeShadr3.setScale(sf::Vector2f(1.0f, 1.0));
                            window.draw(lifeShadr3);
                        }
                    }
                }

                // Chronometer
                std::stringstream ss;
                if (chronometer.getElapsedTime().asSeconds() > 1){
                    if (maxTime <= 0){ // if the time reaches 0
                        ss << "TIMES UP";
                        Chrono.setString(ss.str());
                        Chrono.setPosition(850, 55);
                        window.draw(Chrono);
                        window.display();
                        sf::sleep(sf::seconds(3));
                        if (firstPlayer.HP < secondPlayer.HP){
                            firstPlayer.lives--;
                            // death animation
                        }
                        else if (secondPlayer.HP < firstPlayer.HP){
                            secondPlayer.lives--;
                            // death animation
                        }
                        music.stop();
                        launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                    }
                    ss << maxTime; // update the time (decreases per second)
                    Chrono.setString(ss.str());
                    maxTime--;
                    chronometer.restart();
                }
                window.draw(Chrono);

            



        } else if (gameState == PAUSED) {
        window.clear(sf::Color::Black);
        window.draw(backToGameText);
        window.draw(backToMenuText);
        window.draw(closeGameText);
    } 

        window.display();
    }
}

void endGameMenu(sf::RenderWindow& window, int character, sf::Font font, bool musicOn, int chosenChar1, int chosenChar2, Character firstPlayer, Character secondPlayer, sf::Music& music, sf::Joystick controller1) {

    firstPlayer.lives = 3;
    secondPlayer.lives = 3;

    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    // Create menu options
    sf::Text replayOption("Play again", font, 50);
    sf::Text menuOption("Return to menu", font, 50);
    sf::Text quitOption("Quit", font, 50);

    // Position menu options
    replayOption.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);
    menuOption.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    quitOption.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);

    // Menu options positions
    int replayOptionPos = window.getSize().y / 2 - 100;
    int menuOptionPos = window.getSize().y / 2;
    int quitOptionPos = window.getSize().y / 2 + 100;

    // Initial choice position
    int choicePos = replayOptionPos;

    bool wasButton0Pressed = false;
    bool wasButton3Pressed = false;
    bool wasSPressed = false;
    bool wasZPressed = false;

    const float JoystickSensitivity = 7.5f; // Adjust as needed
    const float JoystickNeutralThreshold = 7.5f; // Adjust as needed
    // Previous joystick position
    float prevY = 0.0f;

    // Game loop
    while (window.isOpen()) {
        float currentY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Color Update depending on your choice
            if (choicePos == replayOptionPos) {
                replayOption.setFillColor(sf::Color::Red);
                menuOption.setFillColor(sf::Color::White);
                quitOption.setFillColor(sf::Color::White);
            } else if (choicePos == menuOptionPos) {
                replayOption.setFillColor(sf::Color::White);
                menuOption.setFillColor(sf::Color::Red);
                quitOption.setFillColor(sf::Color::White);
            } else if (choicePos == quitOptionPos) {
                replayOption.setFillColor(sf::Color::White);
                menuOption.setFillColor(sf::Color::White);
                quitOption.setFillColor(sf::Color::Red);
            }

            // Check if menu options are clicked
            if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY < -JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && choicePos == menuOptionPos) {
                if (!wasButton3Pressed && !wasZPressed) {
                    choicePos = replayOptionPos;
                    wasButton3Pressed = true;
                    wasZPressed = true;
                }
            } 
            else if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY > JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && choicePos == menuOptionPos) {
                if (!wasButton0Pressed && !wasSPressed) {
                    choicePos = quitOptionPos;
                    wasButton0Pressed = true;
                    wasSPressed = true;
                }
            } 
            else if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY > JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && choicePos == replayOptionPos) {
                if (!wasButton0Pressed && !wasSPressed) {
                    choicePos = menuOptionPos;
                    wasButton0Pressed = true;
                    wasZPressed = true;
                }
            } 
            else if (((std::abs(currentY - prevY) > JoystickSensitivity && currentY < -JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && choicePos == quitOptionPos){
                if (!wasButton3Pressed && !wasZPressed) {
                    choicePos = menuOptionPos;
                    wasButton3Pressed = true;
                    wasZPressed = true;
                }
            } else {
                wasButton3Pressed = false;
                wasButton0Pressed = false;
                wasZPressed = false;
            }
            if (controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (choicePos == replayOptionPos) {
                    // Replay game
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                } else if (choicePos == menuOptionPos) {
                    // Return to menu
                    system("Pixel-Showdown.exe");
                    system("taskkill /F /IM Pixel-Showdown.exe");
                } else if (choicePos == quitOptionPos) {
                    // Quit game
                    window.close();
                }
            }
        }

        // Draw menu options
        window.clear();
        window.draw(s);
        window.draw(replayOption);
        window.draw(menuOption);
        window.draw(quitOption);
        window.display();
    }
}
