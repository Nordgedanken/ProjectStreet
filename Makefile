default:

DC=docker-compose

up: up-mysql up-mysql_vmail post-makeproject up-apache up-mailserver

down: 
	$(DC) down

build: makeproject build-mysql build-apache

pull: 
	$(DC) pull


#--- project ---

makeproject: 
	mkdir -p private
	GITTAG="$$(git rev-parse --short HEAD),$$(TZ=UTC git show -s --format=%cd --date=local HEAD)" \
	$(DC) build makeproject

post-makeproject:
	$(DC) run --rm makeproject

#--- apache ---

build-apache:
	$(DC) build apache

up-apache:
	$(DC) up -d apache

rm-apache:
	$(DC) stop apache && $(DC) rm -f apache

exec-apache:
	docker exec -it $(shell $(DC) ps -q apache) bash


# --- mysql ---

build-mysql: 
	$(DC) build mysql

up-mysql:
	$(DC) up -d mysql

rm-mysql:
	$(DC) stop mysql && $(DC) rm -f mysql
	
# --- mysql_vmail ---

up-mysql_vmail:
	$(DC) up -d mysql_vmail

rm-mysql_vmail:
	$(DC) stop mysql_vmail && $(DC) rm -f mysql_vmail
	
# --- mailserver ---

up-mailserver:
	$(DC) up -d mailserver

# --- backups ---

backup-mysql: 
	$(DC) stop mysql
	$(DC) run --rm mysql-backup
	$(DC) start mysql
	$(DC) restart apache

backup-project: 
	$(DC) run --rm project-backup
