#pragma once

/// <summary>
/// Ž©ŒR‚©“GŒR‚©
/// </summary>
enum class TEAM_TAG
{
	PLAYER = 0,
	ENEMY = 1,
	MAX = 2,
};

inline TEAM_TAG GetAnoterTag(TEAM_TAG tag)
{
	return static_cast<TEAM_TAG>((static_cast<int>(tag) + 1) % static_cast<int>(TEAM_TAG::MAX));
}