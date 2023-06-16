#include "scoreboard.h"

// Updates current goal based on stage data.
void scoreboard::setEggGoal(const stageData& stage)
{
    eggGoal = stage.getGoal();
}

// Updates goal, stage score, and goal flag.
void scoreboard::update(const stageData& stage)
{
    setEggGoal(stage);
    resetGoalFlag();
    initStageScore();
}

void scoreboard::displayScoreBoard(Graphics& gfx, const int lives) const
{
    unsigned int cellsPerRow = min(eggGoal-stageEggScore, BOARD_WRAP);
    unsigned int width = (cellsPerRow * BOARD_SCALE);
    unsigned int padding = ((cellsPerRow - 1) * BOARD_MARGIN);
    width += padding;

    unsigned int centerOffset = (gfx.ScreenWidth / 2) - (width/2);
    unsigned int x = BOARD_MARGIN;
    unsigned int y = BOARD_MARGIN;

    for (unsigned int i = 0; i < eggGoal - stageEggScore; ++i) {
        x = centerOffset + (i % BOARD_WRAP * (BOARD_MARGIN + BOARD_SCALE));
        y = BOARD_MARGIN + (i / BOARD_WRAP * (BOARD_MARGIN + BOARD_SCALE));
        gfx.DrawRectDim(x, y, BOARD_SCALE, BOARD_SCALE, Colors::LightGray);
    }

    drawLives(gfx, lives);
}

// Sets off goal flag (for signalling) if threshold reached.
void scoreboard::eggScoreIncrement()
{
    totalEggScore++;
    stageEggScore++;
    if (iseggGoalReached()) {
        flag_GoalReached = true;
    }
}

void scoreboard::resetGoalFlag()
{
    flag_GoalReached = false;
}

void scoreboard::drawLives(Graphics& gfx, const int lives) const
{
    int x;
    int spriteSize = 20;
    for (int i = 0; i < lives - 1; i++) {
        x = BOARD_MARGIN + (i * (BOARD_MARGIN + spriteSize));
        SpriteCodex::DrawLife(gfx, x, BOARD_MARGIN);
    }
}
