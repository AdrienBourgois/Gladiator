// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class GLADIATORGAME_API BaseCharacter
{
public:
	BaseCharacter();
	BaseCharacter(int Life);
	virtual ~BaseCharacter();
	
	virtual void Attack();
	virtual void ReceiveDomage();
	virtual void Death();
	virtual void Move();

	int _Life;
};
