global_states = {
    change_level_show_time = 50,
    enemies = {
        enemy_shoot_chance = 1,
        enemy_movement_delay = 50,
        enemy_dead_animation = {
            {
                { '(', '#', '0', '#', ')' }
            },
            {
                { '*', 'X', '*', 'X', '*' }
            },
            {
                { '*', '.', '*', '.', '*' }
            },
            {
                { ' ', '.', '+', '.', ' ' }
            },
            {
                { ' ', ' ', '.', ' ', ' ' }
            }
        },
        enemy_animation_frame_delay = 5,
        basic_enemy = {
            enemy_movement_delay = 50,
            health = 2,
            score = 100,
            appearance = {
                { '(', '0', '.', '0', ')' }
            },
            color = "ENEMY_COLOR"
        },
        shooter_enemy = {
            enemy_shoot_delay = 10,
            health = 1,
            score = 200,
            appearance = {
                { '\\', '-', '|', '-', '/' }
            },
            enemy_bullet_appearance = {
                { '*' }
            },
            color = "ENEMY_COLOR",
            bullet_color = "ENEMY_BULLET_COLOR"
        }
    },

    player = {
        player_shoot_delay = 20,
        player_max_bullets = 10,
        health = 3,
        player_appearance = {
            { '/', '_', 'T', '_', '\\' }
        },
        player_bullet_appearance = {
            { '|' }
        },
        color = "PLAYER_COLOR",
        bullet_color = "PLAYER_BULLET_COLOR"
    }
}

colors = {
    PLAYER_COLOR = "#FF0000",
    PLAYER_BULLET_COLOR = "#FF0000",
    ENEMY_COLOR = "#7CFC00",
    ENEMY_BULLET_COLOR = "#ADFF2F",
    BORDER_COLOR = "#191970",
    TEXT_COLOR = "#FFFFFF",
    SELECTED_TEXT_COLOR = "#FFFFFF"
}

sounds = {
    PLAYER_SHOOT_SOUND = "sounds/shoot.mp3",
    ENEMY_SHOOT_SOUND = "sounds/enemy_shoot.mp3",
    BACKGROUND_MUSIC = "sounds/background.mp3",
    ENEMY_EXPLOSION_SOUND = "sounds/explosion.mp3"
}

levels_queue = {
    { "level_1", "level_2" }
}
