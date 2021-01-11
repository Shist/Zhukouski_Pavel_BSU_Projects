"""baseline

Revision ID: 9b898740929f
Revises: 
Create Date: 2019-08-06 11:41:56.265057

"""
import sys
from alembic import op
import sqlalchemy as sa
from pathlib import Path

root_path = Path(__file__).resolve().parent.parent.parent.parent
sys.path.insert(0, str(root_path))

import backend.model



# revision identifiers, used by Alembic.
revision = '9b898740929f'
down_revision = None
branch_labels = None
depends_on = None


def upgrade():
    pass


def downgrade():
    pass
