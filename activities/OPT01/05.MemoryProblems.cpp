// Type definitions
struct SkinColorT
{
    uint8_t uRed;   // 0 - 255 value
    uint8_t uGreen; // 0 - 255 value
    uint8_t uBlue;  // 0 - 255 value
};

static const uint32_t MONSTER_MAX_NAMELENGTH = 100;

struct MonsterT
{
    char8_t             strName[MONSTER_MAX_NAMELENGTH];
    MonsterModelTypeE   eModelType;
    SkinColorT          SkinColor;
    float_t             fSpeed;         // 0.0 - 1.0 scale value
    Bool                bIsDead;
    Bool                bIsUnconscious;
    Bool                bIsHidden;
    Bool                bIsInvulnerable;
    Bool                bIsEngaged;
    uint8_t             uJumpAbility;   // 0 - 255 value
};

static const uint32_t TREASURE_MAX_NAMELENGTH = 64;

struct TreasureT
{
    char8_t strName[TREASURE_MAX_NAMELENGTH];
    float_t fValue;                          // 0.0 - 1.0
    Bool    bWasFound;
};

// Game objects
static const uint32_t MAX_MONSTERS = 6;
static const uint32_t MAX_TREASURES = 8;
static MonsterT *sMonsterObjects[MAX_MONSTERS];
static TreasureT *sTreasureObjects[MAX_TREASURES];

// Main Game Functions
void GameStart(void)
{
    LoadMonsterModels();

    // Clear our object arrays
    memset(sMonsterObjects, 0, sizeof(sMonsterObjects));
    memset(sTreasureObjects, 0, sizeof(sTreasureObjects));

    LoadEnvironment();
}

void GameProcess(void)
{
    ProcessTreasures();

    ProcessMonsters();
}

void GameEnd(void)
{
    for (uint32_t uMonsterIndex = 0; uMonsterIndex < MAX_MONSTERS; uMonsterIndex++)
    {
        // Kill off all of the monsters
        KillMonster(sMonsterObjects[uMonsterIndex]);
        sMonsterObjects[uMonsterIndex] = NULL;
    }

    for (uint32_t uTreasureIndex = 0; uTreasureIndex < MAX_TREASURES; uTreasureIndex++)
    {
        // Destroy all of the treasures
        DestroyTreasure(sTreasureObjects[uTreasureIndex]);
        sTreasureObjects[uTreasureIndex] = NULL;
    }

}

void ProcessMonsters(void)
{
    uint32_t uMonsterIndex;
    uint32_t uNumMonsters = 0;

    // Process all of the monsters
    for (uMonsterIndex = 0; uMonsterIndex < MAX_MONSTERS; uMonsterIndex++)
    {
        if (NULL != sMonsterObjects[uMonsterIndex])
        {
            if (MonsterIsDead(sMonsterObjects[uMonsterIndex]))
            {
                // Kill this monster off
                KillMonster(sMonsterObjects[uMonsterIndex]);
                sMonsterObjects[uMonsterIndex] = NULL;
            }
        }

        if (NULL != sMonsterObjects[uMonsterIndex])
        {
            MoveMonster(sMonsterObjects[uMonsterIndex]);
            DrawMonster(sMonsterObjects[uMonsterIndex]);

            // Count up the total number of monsters
            uNumMonsters++;
        }
    }

    // Randomly Spawn up to (MAX_MONSTERS - uNumMonsters) monsters
    uint32_t uNumNewMonsters = GetRandom (0, (MAX_MONSTERS - uNumMonsters) + 1);

    if (uNumNewMonsters > 0)
    {
        for (uMonsterIndex = 0; uMonsterIndex < MAX_MONSTERS; uMonsterIndex++)
        {
            if ((uNumNewMonsters > 0) && (NULL == sMonsterObjects[uMonsterIndex]))
            {
                sMonsterObjects[uMonsterIndex] = SpawnMonster();
                uNumNewMonsters--;
            }
        }
    }
    SysAssert(0 == uNumNewMonsters);
}

// Monster functions
MonsterT *SpawnMonster(void)
{
    // Create the object
    MonsterT *pMonster = (MonsterT *)MemHAlloc(HEAP, sizeof(MonsterT),  0, "MONSTER_OBJ");

    // Get a random monster type
    pMonster->eModelType = GetRandom(0, MODELTYPE_MAX);

    // Initialize some info
    pMonster->bIsDead = FALSE;
    pMonster->bIsUnconscious = FALSE;
    pMonster->bIsHidden = FALSE;
    pMonster->bIsInvulnerable = FALSE;
    pMonster->bIsEngaged = FALSE;

    return (pMonster);
}

void KillMonster(MonsterT *pMonster)
{
    // Destroy the monster object
    MemFree(pMonster);
}

// Treasure Functions
TreasureT *SpawnTreasure(void)
{
    // Create the object
    TreasureT *pTreasure = (TreasureT *)MemHAlloc(HEAP, sizeof(TreasureT), 0, "TREASURE_OBJ");

    // Initialize some info
    pTreasure->bWasFound = FALSE;

    return (pTreasure);
}

void DestroyTreasure(TreasureT *pTreasure)
{
    // Destroy the treasure object
    MemFree(pTreasure);
}

void ProcessTreasures(void)
{
    uint32_t uTreasureIndex;
    uint32_t uNumTreasures = 0;

    // Process all of the treasures
    for (uTreasureIndex = 0; uTreasureIndex < MAX_TREASURES; uTreasureIndex++)
    {
        if (NULL != sTreasureObjects[uTreasureIndex])
        {
            // If a player found a treasure, it is no longer useful, so destroy the object
            if (TreasureWasFound(sTreasureObjects[uTreasureIndex]))
            {
                // Destroy the empty treasure
                DestroyTreasure(sTreasureObjects[uTreasureIndex]);
                sTreasureObjects[uTreasureIndex] = NULL;
            }
        }

        if (NULL != sTreasureObjects[uTreasureIndex])
        {
            // Count up the total number of treasure that still exist
            uNumTreasures++;
        }
    }

    // Randomly Spawn up to (MAX_TREASURES - uNumTreasures) new treasures
    uint32_t uNumNewTreasures = GetRandom(0, (MAX_TREASURES - uNumTreasures) + 1);

    if (uNumNewTreasures > 0)
    {
        for (uTreasureIndex = 0; uTreasureIndex < MAX_TREASURES; uTreasureIndex++)
        {
            if ((uNumNewTreasures > 0) && (NULL == sTreasureObjects[uTreasureIndex]))
            {
                sTreasureObjects[uTreasureIndex] = SpawnTreasure();
                uNumNewTreasures--;
            }
        }
    }
}
