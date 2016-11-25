// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
}
ABaseCharacter::ABaseCharacter(int Life)
{
	_Life = Life;
}
ABaseCharacter::~ABaseCharacter()
{
}

void ABaseCharacter::Attack()
{
	
}

void ABaseCharacter::ReceiveDamage(int dmg)
{
	this->_Life -= dmg;
}

void ABaseCharacter::Death()
{
	
}

void ABaseCharacter::Move()
{
	
}