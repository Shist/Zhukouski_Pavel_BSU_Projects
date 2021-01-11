"""
AxApproval field type functions - before, after / insert, update, delete

If you want sequence - add children of previous step.
When user approves - he approves in all branches.
Field must contain list of pending actions.
When user added - AxMessage created in created branch with message about
    'You was invited to review and approve record'
When user approves - AxMessage created in all branches that user is set

Incase you want to email added person - you must do it in action python code
like so:
    ============================================================================

    initiator_email = ax.row.approval1.get('initiator')
    modifications = ax.row.approval1.get('modifications' , [])

    for mod in modifications:
        if mod['type'] == 'add':
            subject = f'⛏️ You was invited to approve - [{ax.tom_label}]'
            address = mod['reviewer']
            email_text = f"⛏️ You was invited to approve  - [{ax.tom_label}]"
            email_html = (
                f"⛏️ You was invited to approve Ax form - [{ax.tom_label}]"
                f"<br><a href='{ax.form_url}' >Open form [{ax.tom_label}]</a>"
            )
            await ax.email(
                to=address,
                text=email_text,
                html=email_html,
                subject=subject)

            ax.print(f'Email was sent to - {address} \n')
            ax.print(f'Current user email - {ax.user_email} \n')
            ax.print(f'Initiator email - {initiator_email} \n')

    ============================================================================

If you want a default approval path - you can create in in insert action like so

    field.value = {
        initiator: 'enf644@gmail.com',
        created: int(time.time()),
        branches: [{
            id: str(uuid.uuid4())
            reviewer: 'admin@someone.com',
            created: int(time.time()),
            status: 1,
            branches: [],
        }],
    }


Statuses:
    0 - waiting,
    1 - action needed
    3 - question added
    4 - approved
    5 - rejected

Value json structure:
    {
        initiator: 'enf644@gmail.com',
        created: 1574079223249,
        modified: 1574079223249,
        branches: [{
            id: '831d7d35-1b29-48bd-add0-e928e7c9e87f'
            reviewer: 'admin@someone.com',
            created: 1574079223249,
            modified: 1574079223249,
            status: 1,
            branches: [],
            resolution: 'I agree to this'
        }],
        awaitingActions: [
            {
                reviewer: 'admin@someone.com',
                created: 1574079223249
            }
        ],
        modifications: {
            {
                type: 'add',
                branchId: '831d7d35-1b29-48bd-add0-e928e7c9e87f',
                reviewer: 'boosov@gmail.com'
            },
            {
                type: 'status',
                branchId: '831d7d35-1b29-48bd-add0-e928e7c9e87f',
                reviewer: 'boosov@gmail.com'
                status: 3,
                resolution: 'I do not agree
            }
        }
    }

"""
import uuid
import time
from backend.model import AxMessage, AxMessageThread
import backend.misc as ax_misc
# import backend.emails as ax_emails


async def before_update(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Takes old value of field. Then using modifications modifies it.
        Approval statuses recieved from form are not used, only modifications.
        We walk over every branch of approval tree checking if action is needed

        Avalible actions are:
            add - invite new reviewer
            status - change branch status

        On every action the AxMessage is created for history.
    """
    del tobe_form, action
    current_user_email = current_user["email"]
    current_user_guid = current_user["user_id"]

    old_value = None
    if before_form.row_guid is None:
        old_value = field.value
    else:
        old_value = next(
            (fld.value for fld in before_form.fields if fld.guid == field.guid),
            None)
    modifications = field.value['modifications']

    async def create_message(thread_guid, text):
        thread = None
        if thread_guid and thread_guid != 'None':
            thread = db_session.query(AxMessageThread).filter(
                AxMessageThread.guid == uuid.UUID(str(thread_guid))
            ).first()
        if not thread:
            thread = AxMessageThread()
            thread.guid = uuid.UUID(str(thread_guid))
            db_session.add(thread)
            db_session.flush()

        new_message = AxMessage()
        new_message.author_guid = ax_misc.guid_or_none(current_user_guid)
        new_message.author_email = current_user_email
        new_message.text = text
        new_message.data_json = None
        new_message.thread_guid = thread.guid
        db_session.add(new_message)
        db_session.flush()

    async def check_if_action_needed(branch):
        """ Checks if modification list contains action for branch """
        now_date = int(time.time())
        if (not modifications or (
                current_user_email != branch.get('reviewer', None)
                and current_user_email != branch.get('initiator', None))):
            return branch
        for mod in modifications:
            if mod['branchId'] == branch['id']:
                already_presend = next(
                    (brch for brch in branch.get('branches')
                     if brch.get('reviewer') == mod.get('reviewer')),
                    None)

                text = None
                thread_guid = None
                new_branch_guid = str(uuid.uuid4())

                # Add new reviewer
                if mod['type'] == 'add' and not already_presend:

                    reviewer = mod['reviewer']
                    branch['branches'].append({
                        "id": new_branch_guid,
                        "reviewer": reviewer,
                        "created": now_date,
                        "status": 1,
                        "branches": [],
                    })
                    branch['modified'] = now_date
                    # TODO get this from locale!

                    # Add AxMessage
                    text = f'⛏️ [New reviewer was added]:\n {reviewer}'
                    thread_guid = branch['id'] or new_branch_guid
                    await create_message(thread_guid=thread_guid, text=text)

                    # If reviewer added to root branch - the branch_id is None
                    # and we cant add to thread. So we add this message to
                    # newly created branch
                    if not branch['id']:
                        thread_guid = new_branch_guid

                # Change status
                if mod['type'] == 'status':
                    resolution = mod['resolution']
                    status = int(mod['status'])
                    branch['status'] = status
                    branch['resolution'] = resolution
                    branch['modified'] = now_date
                    thread_guid = branch['id']

                    if status == 3:
                        text = f'⛏️ [Question was added]:\n {resolution}'
                    if status == 4:
                        text = f'⛏️ [Approval recieved]:\n {resolution}'
                    if status == 5:
                        text = f'⛏️ [Rejected]:\n {resolution}'

                    # Create AxMessage
                    await create_message(thread_guid=thread_guid, text=text)

        return branch

    async def check_node(branch):
        """ Check if modifications are needed for current branch and all
            chlidrens (recursive) """
        for idx, sub_brunch in enumerate(branch['branches']):
            branch['branches'][idx] = await check_node(branch=sub_brunch)

        branch = await check_if_action_needed(branch=branch)
        return branch

    # Walk over all nodes - check if action is needed
    field.value = await check_node(
        branch=old_value)

    #  In check_node we modified before_form. To pass new modifications
    # to action python and db, we need to rewrite it
    field.value["modifications"] = modifications

    field.needs_sql_update = True
    return field.value


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Create first value. Save initiator, then do before_update. """
    user_email = current_user["email"]
    now_date = int(time.time())
    new_branches = []

    if not field.value:
        return field.value

    for rev in field.value['branches']:
        # id will be replaced inside check_if_action_needed
        new_branches.append({
            "id": str(uuid.uuid4()),
            "reviewer": rev["reviewer"],
            "created": now_date,
            "status": 1,
            "branches": []
        })

    field.value = {
        "id": None,
        "initiator": user_email,
        "created": now_date,
        "branches": new_branches,
        "modifications": field.value["modifications"]
    }

    return await before_update(
        db_session=db_session,
        field=field,
        before_form=before_form,
        tobe_form=tobe_form,
        action=action,
        current_user=current_user)
